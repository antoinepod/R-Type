/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** UDPServer.cpp
*/

#include "UDPServer.hpp"

UDPServer::UDPServer(boost::asio::io_context& io_context) : _socket(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 8080)) {
//    _timer = std::make_shared<boost::asio::deadline_timer>(io_context, boost::posix_time::milliseconds(16));
    srand((int)time(0));

    _nbEnemy = 0;

    for (int i = 0; i < THREADS_NBR; i++) {
        _threadPool.emplace_back(&UDPServer::StartReceive, this);
    }
    _threadPool.emplace_back(&UDPServer::UpdateGame, this);

    _gameObject.reserve(sizeof(Network::Object) * 100);
    CreateGameState();

    _playerFrames[1] = 0;
    _playerFrames[2] = 0;
    _playerFrames[3] = 0;
    _playerFrames[4] = 0;
}

UDPServer::~UDPServer() = default;

void UDPServer::StartReceive() {
//    _timer->async_wait(boost::bind(&UDPServer::UpdateGame, this));
    _socket.async_receive_from(boost::asio::buffer(_recvBuffer), _remoteEndpoint,boost::bind(&UDPServer::Receive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    // Debug
    // std::cout << _remoteEndpoint.address().to_string() << ": " << std::to_string(_recvBuffer.data()[0]) << std::endl;

    auto search = _myMap.find(_remoteEndpoint.address().to_string());
    if (!_myMap.empty() && search != _myMap.end()) {
        // Debug
        // for (auto &i: _myMap)
        //     std::cout << i.first << "  " << i.second << std::endl;

        _mutex.lock();

        int playerIndex = FindPlayer(search->second);

        if (playerIndex == -1) {
            _mutex.unlock();
            return;
        }

        switch (_recvBuffer.data()[0]) {
            case Action::SIMPLE_SHOOT:
                CreateBullet(_gameObject[playerIndex], BulletType::SIMPLE);
                break;
            case Action::LASER_SHOOT:
                CreateBullet(_gameObject[playerIndex], BulletType::LASER);
                break;
            case Action::ROCKET_SHOOT:
                CreateBullet(_gameObject[playerIndex], BulletType::ROCKET);
                break;
            case Action::LEFT:
                if (_gameObject[playerIndex].getX() > 0) {
                    _gameObject[playerIndex].setX(_gameObject[playerIndex].getX() - 4);
                    _playerFrames[search->second] = 0;
                    _gameObject[playerIndex].setFrame(0);
                }
                break;
            case Action::RIGHT:
                if (_gameObject[playerIndex].getX() < 1500 - 66) {
                    _gameObject[playerIndex].setX(_gameObject[playerIndex].getX() + 4);
                    _playerFrames[search->second] = 0;
                    _gameObject[playerIndex].setFrame(0);
                }
                break;
            case Action::UP:
                if (_gameObject[playerIndex].getY() > 0) {
                    _gameObject[playerIndex].setY(_gameObject[playerIndex].getY() - 4);
                    _playerFrames[search->second]++;
                    if (_playerFrames[search->second] >= 10)
                        _gameObject[playerIndex].setFrame(2);
                    else
                        _gameObject[playerIndex].setFrame(1);
                }
                break;
            case Action::DOWN:
                if (_gameObject[playerIndex].getY() < 900 - 34) {
                    _gameObject[playerIndex].setY(_gameObject[playerIndex].getY() + 4);
                    _playerFrames[search->second]++;
                    if (_playerFrames[search->second] >= 10)
                        _gameObject[playerIndex].setFrame(-2);
                    else
                        _gameObject[playerIndex].setFrame(-1);
                }
                break;
            case Action::NONE:
                _playerFrames[search->second] = 0;
                _gameObject[playerIndex].setFrame(0);
                break;
            case Action::LEVEL1:
                Level_1();
                break;
            case Action::LEVEL2:
                Level_2();
                break;
            case Action::LEVEL3:
                Level_3();
                break;
            case Action::LEVEL4:
                Level_4();
                break;
            case Action::LEVEL5:
                Level_5();
                break;
        }
        _mutex.unlock();

        //if (_recvBuffer.data()[0] == static_cast<unsigned char>(RType::Events::QUIT)) {
        //    _myMap.erase(_remoteEndpoint.address().to_string());
        //    if (_myMap.size() == 0) {
        //        for (auto& t : _threadPool)
        //            t.join();
        //        return;
        //    }
        //}
        //        }
    }
}


void UDPServer::Receive(const boost::system::error_code& error, std::size_t) {
    if (!error) {
//        if (_gameObject.size() > 1)
//            _gameObject[1].setX(_gameObject[1].getX() + _gameObject[1].getCelerity());
        _mutex.lock();
        Network::Seria::S_erialize(_gameObject, &_buf);
        _mutex.unlock();
        std::string strBuf(boost::asio::buffers_begin(_buf.data()),boost::asio::buffers_end(_buf.data()));
        boost::shared_ptr<std::string> message(new std::string(strBuf));
        //            std::cout << "" << *message << std::endl;
        //std::cout << "Serialized data size: " << _buf.size() << "and mess length: " << message->length() << std::endl;
        _socket.async_send_to(boost::asio::buffer(*message), _remoteEndpoint, boost::bind(&UDPServer::Send, this, message, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
        _buf.consume(_buf.size());
        StartReceive();
    }
}

int UDPServer::FindPlayer(int id) {
    for (int i = 0; i < _gameObject.size(); i++) {
        if (_gameObject[i].getType() == ObjectType::PLAYER && _gameObject[i].getId() == id)
            return i;
    }
    return -1;
}

void UDPServer::Send(boost::shared_ptr<std::string>, const boost::system::error_code&,std::size_t) {}


// Create GameObjects

void UDPServer::CreateGameState() {
    Network::Object gameState;
    gameState.setType(ObjectType::GAME_STATE);
    gameState.setGameState(GameState::WAITING);
    _mutex.lock();
    _gameObject.push_back(gameState);
    _mutex.unlock();
}

void UDPServer::CreatePlayer(const std::string& ip, int id, const std::string& name) {
    for (auto & object: _gameObject) {
        if (object.getType() == ObjectType::UNDEFINED) {
            object.setName(name);
            object.setX(100);
            object.setY(420);
            object.setCelerity(4);
            object.setHealth(200);
            object.setId(id);
            object.setType(ObjectType::PLAYER);
            object.setFrame(0);
            object.setStrength(10);
            object.setBullet(BulletType::SIMPLE);

            _myMap.insert(std::pair<std::string, int>(ip, id));
            return;
        }
    }

    Network::Player player;
    player.setName(name);
    player.setX(100);
    player.setY(420);
    player.setCelerity(4);
    player.setHealth(200);
    player.setId(id);
    player.setType(ObjectType::PLAYER);
    player.setFrame(0);
    player.setStrength(10);
    player.setBullet(BulletType::SIMPLE);

    _myMap.insert(std::pair<std::string, int>(ip, id));

    _mutex.lock();
    _gameObject.push_back(player);
    _mutex.unlock();
}

void UDPServer::CreateBullet(Network::Object sender, BulletType bulletType) {
    int strength = 0;
    switch (bulletType) {
        case BulletType::SIMPLE:
            CreateSound(SoundType::SHOOT_SIMPLE);
            strength = 10;
            break;
        case BulletType::LASER:
            CreateSound(SoundType::SHOOT_LASER);
            strength = 50;
            break;
        case BulletType::ROCKET:
            CreateSound(SoundType::SHOOT_ROCKET);
            strength = 100;
            break;
    }

    for (auto & object: _gameObject) {
        if (object.getType() == ObjectType::UNDEFINED) {
            object.setX(sender.getX() + 50.0f);
            object.setY(sender.getY() + 15.0f);
            object.setCelerity(15);
            object.setType(ObjectType::BULLET);
            object.setId(_bulletId++);
            object.setStrength(strength);
            object.setBullet(bulletType);
            object.setExplosion(ExplosionType::MISSILE);
            return;
        }
    }

    Network::Bullet bullet;
    bullet.setX(sender.getX() + 50.0f);
    bullet.setY(sender.getY() + 15.0f);
    bullet.setCelerity(15);
    bullet.setType(ObjectType::BULLET);
    bullet.setId(_bulletId++);
    bullet.setStrength(strength);
    bullet.setBullet(bulletType);
    bullet.setExplosion(ExplosionType::MISSILE);

    _gameObject.push_back(bullet);
}

void UDPServer::CreateEnemy(int id, float x, float y) {
    _nbEnemy++;

    for (auto & object: _gameObject) {
        if (object.getType() == ObjectType::UNDEFINED) {
            object.setX(x);
            object.setY(y);
            object.setCelerity(1);
            object.setHealth(100);
            object.setType(ObjectType::ENEMY);
            object.setExplosion(ExplosionType::SMALL);
            object.setBullet(BulletType::SIMPLE);
            object.setId(id);
            return;
        }
    }

    Network::Enemy enemy;
    enemy.setX(x);
    enemy.setY(y);
    enemy.setCelerity(1.1);
    enemy.setHealth(200);
    enemy.setType(ObjectType::ENEMY);
    enemy.setExplosion(ExplosionType::SMALL);
    enemy.setBullet(BulletType::SIMPLE);
    enemy.setId(id);

    _gameObject.push_back(enemy);
}

void UDPServer::CreateExplosion(ExplosionType explosionType, float x, float y) {
    switch (explosionType) {
        case ExplosionType::MISSILE:
            CreateSound(SoundType::EXPLOSION_MISSILE);
            break;
        case ExplosionType::SMALL:
            CreateSound(SoundType::EXPLOSION_SMALL);
            break;
        case ExplosionType::MEDIUM:
            CreateSound(SoundType::EXPLOSION_MEDIUM);
            break;
        case ExplosionType::BIG:
            CreateSound(SoundType::EXPLOSION_BIG);
            break;
    }

    for (auto & object: _gameObject) {
        if (object.getType() == ObjectType::UNDEFINED) {
            object.setX(x);
            object.setY(y);
            object.setType(ObjectType::EXPLOSION);
            object.setFrame(0);
            object.setExplosion(explosionType);
            object.setId(_explosionId++);
            _explosionFrames[_explosionId] = 0;
            return;
        }
    }

    Network::Explosion explosion;
    explosion.setX(x);
    explosion.setY(y);
    explosion.setType(ObjectType::EXPLOSION);
    explosion.setFrame(0);
    explosion.setExplosion(explosionType);
    explosion.setId(_explosionId++);
    _explosionFrames[_explosionId] = 0;

    _gameObject.push_back(explosion);
}

void UDPServer::CreateSound(SoundType soundType) {
    for (auto & object: _gameObject) {
        if (object.getType() == ObjectType::UNDEFINED) {
            object.setType(ObjectType::SOUND);
            object.setId(0);
            object.setSound(soundType);
            return;
        }
    }

    Network::Sound sound;
    sound.setType(ObjectType::SOUND);
    sound.setId(0);
    sound.setSound(soundType);

    _gameObject.push_back(sound);
}


//Update GameObjects

void UDPServer::UpdateGame() {
    while (true) {
        _mutex.lock();
        for (auto &object: _gameObject) {
            // Debug
            //            std::cout << "Object: " << object.getType() << " id:" << object.getId() << " pos: " << object.getX() << " " << object.getY() << std::endl;
            switch (object.getType()) {
                case ObjectType::GAME_STATE:
                    UpdateGameState(object);
                    break;
                case ObjectType::BULLET:
                    UpdateBullet(object);
                    break;
                case ObjectType::ENEMY:
                    UpdateEnemy(object);
                    break;
                case ObjectType::POWER_UP:
                    break;
                case ObjectType::EXPLOSION:
                    UpdateExplosion(object);
                    break;
                case ObjectType::SOUND:
                    UpdateSound(object);
                    break;
                default:
                    break;
            }
        }
        _mutex.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}

void UDPServer::UpdateGameState(Network::Object &gameState) {
//    if (gameState.getGameState() >= GameState::LEVEL_1 && gameState.getGameState() <= GameState::LEVEL_5 && _nbEnemy == 0)
//            gameState.setGameState(GameState::WIN);
}

void UDPServer::UpdateEnemy(Network::Object & enemy) {
//    if (enemy.getX() > -50)
//        enemy.setX(enemy.getX() - enemy.getCelerity());
//    else
//        enemy.setType(ObjectType::UNDEFINED);
}

void UDPServer::UpdateBullet(Network::Object & bullet) {
    if (bullet.getX() > 0 && bullet.getX() < 1500)
        bullet.setX(bullet.getX() + bullet.getCelerity());
    else
        bullet.setType(ObjectType::UNDEFINED);

    for (auto & object: _gameObject) {
        if (object.getType() == ObjectType::ENEMY) {
            if (CheckCollision(object, bullet)) {
                if (bullet.getBullet() == BulletType::ROCKET)
                    CreateExplosion(ExplosionType::MISSILE, object.getX() - 30, object.getY());
                object.setHealth(object.getHealth() - bullet.getStrength());
                bullet.setType(ObjectType::UNDEFINED);
                if (object.getHealth() <= 0) {
                    CreateExplosion(object.getExplosion(), object.getX(), object.getY());
                    if (object.getType() == ObjectType::ENEMY)
                        _nbEnemy--;
                    object.setType(ObjectType::UNDEFINED);
                }
            }
        }
    }
}

bool UDPServer::CheckCollision(Network::Object & object, Network::Object & bullet) {
    return (object.getX() < bullet.getX() + 10 && object.getX() + 50 > bullet.getX()
            && object.getY() < bullet.getY() + 10 && object.getY() + 50 > bullet.getY());
}

void UDPServer::KillObject(Network::Object object) {
    CreateExplosion(object.getExplosion(), object.getX(), object.getY());
    if (object.getType() == ObjectType::ENEMY)
        _nbEnemy--;
    object.setType(ObjectType::UNDEFINED);
}

void UDPServer::UpdatePowerUp(Network::Object & powerUp) {
}

void UDPServer::UpdateExplosion(Network::Object & explosion) {
    if (_explosionFrames[explosion.getId()] < 50) {
        _explosionFrames[explosion.getId()]++;
        explosion.setFrame(_explosionFrames[explosion.getId()] / 10);
    } else
        explosion.setType(ObjectType::UNDEFINED);
}

void UDPServer::UpdateSound(Network::Object & sound) {
    if (sound.getId() == 0)
        sound.setId(1);
    else
        sound.setType(ObjectType::UNDEFINED);
}

void UDPServer::Level_1() {
    std::cout << "Level 1" << std::endl;

    if (_nbEnemy == 0) {
        CreateEnemy(0, 1350, rand() % 800 + 50);
    }
}

void UDPServer::Level_2() {
    std::cout << "Level 2" << std::endl;

    if (_nbEnemy == 0) {
        CreateEnemy(0, 1350, rand() % 800 + 50);
        CreateEnemy(0, 1350, rand() % 800 + 50);
    }
}

void UDPServer::Level_3() {
    std::cout << "Level 3" << std::endl;

    if (_nbEnemy == 0) {
        CreateEnemy(0, 1350, rand() % 800 + 50);
        CreateEnemy(0, 1350, rand() % 800 + 50);
        CreateEnemy(0, 1350, rand() % 800 + 50);
    }
}

void UDPServer::Level_4() {
    std::cout << "Level 4" << std::endl;

    if (_nbEnemy == 0) {
        CreateEnemy(0, 1350, rand() % 800 + 50);
        CreateEnemy(0, 1350, rand() % 800 + 50);
        CreateEnemy(0, 1350, rand() % 800 + 50);
        CreateEnemy(0, 1350, rand() % 800 + 50);
    }
}

void UDPServer::Level_5() {
    std::cout << "Level 5" << std::endl;

    if (_nbEnemy == 0) {
        CreateEnemy(0, 1350, rand() % 800 + 50);
        CreateEnemy(0, 1350, rand() % 800 + 50);
        CreateEnemy(0, 1350, rand() % 800 + 50);
        CreateEnemy(0, 1350, rand() % 800 + 50);
        CreateEnemy(0, 1350, rand() % 800 + 50);
    }
}
