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

    StartReceive();
    for (int i = 0; i < THREADS_NBR; i++) {
        _threadPool.emplace_back(&UDPServer::StartReceive, this);
    }
    _threadPool.emplace_back(&UDPServer::UpdateGame, this);

    CreateEnemy(0, 1350, rand() % 800 + 50);
    CreateEnemy(0, 1350, rand() % 800 + 50);
    CreateEnemy(0, 1350, rand() % 800 + 50);
    CreateEnemy(0, 1350, rand() % 800 + 50);
    CreateEnemy(0, 1350, rand() % 800 + 50);

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

        int playerIndex = FindPlayer(search->second);

        _mutex.lock();
        switch (_recvBuffer.data()[0]) {
            case Action::SHOOT:
                CreateBullet(_gameObject[playerIndex], BulletType::SIMPLE);
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

void UDPServer::CreatePlayer(const std::string& ip, int id, const std::string& name) {
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

    _mutex.lock();
    _gameObject.push_back(player);
    _mutex.unlock();
    _myMap.insert(std::pair<std::string, int>(ip, id));
}

void UDPServer::CreateBullet(Network::Object & sender, BulletType bulletType) {
    switch (bulletType) {
        case BulletType::SIMPLE:
            CreateSound(SoundType::SHOOT_SIMPLE);
            break;
        case BulletType::LASER:
            CreateSound(SoundType::SHOOT_LASER);
            break;
        case BulletType::ROCKET:
            CreateSound(SoundType::SHOOT_ROCKET);
            break;
    }

    for (auto & object: _gameObject) {
        if (object.getType() == ObjectType::UNDEFINED) {
            object.setX(sender.getX() + 50);
            object.setY(sender.getY() + 15);
            object.setCelerity(15);
            object.setType(ObjectType::BULLET);
            object.setId(_bulletId++);
            object.setStrength(sender.getStrength());
            object.setBullet(bulletType);
            return;
        }
    }

    Network::Bullet bullet;
    bullet.setX(sender.getX() + 50);
    bullet.setY(sender.getY() + 15);
    bullet.setCelerity(15);
    bullet.setType(ObjectType::BULLET);
    bullet.setId(_bulletId++);
    bullet.setStrength(sender.getStrength());
    bullet.setBullet(bulletType);

    _gameObject.push_back(bullet);
}

void UDPServer::CreateEnemy(int id, float x, float y) {
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
    enemy.setHealth(100);
    enemy.setType(ObjectType::ENEMY);
    enemy.setExplosion(ExplosionType::SMALL);
    enemy.setBullet(BulletType::SIMPLE);
    enemy.setId(id);

    _gameObject.push_back(enemy);
}

void UDPServer::CreateExplosion(Network::Object & deadObject, float x, float y) {
    for (auto & object: _gameObject) {
        if (object.getType() == ObjectType::UNDEFINED) {
            object.setX(x);
            object.setY(y);
            object.setType(ObjectType::EXPLOSION);
            object.setFrame(0);
            object.setExplosion(deadObject.getExplosion());
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
    explosion.setExplosion(deadObject.getExplosion());
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

void UDPServer::UpdateGame() {
    while (true) {
        _mutex.lock();
        for (auto &object: _gameObject) {
            // Debug
            //            std::cout << "Object: " << object.getType() << " id:" << object.getId() << " pos: " << object.getX() << " " << object.getY() << std::endl;
            switch (object.getType()) {
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

    for (auto &object: _gameObject) {
        if (object.getType() == ObjectType::ENEMY) {
            if (CheckCollision(object, bullet)) {
                object.setHealth(object.getHealth() - bullet.getStrength());
                if (object.getHealth() <= 0) {
                    object.setType(ObjectType::UNDEFINED);
                    CreateExplosion(object, object.getX(), object.getY());
                }
                bullet.setType(ObjectType::UNDEFINED);
            }
        }
    }
}

void UDPServer::UpdatePowerUp(Network::Object & powerUp) {
}

bool UDPServer::CheckCollision(Network::Object & object, Network::Object & bullet) {
    return (object.getX() < bullet.getX() + 10 &&
            object.getX() + 50 > bullet.getX() &&
            object.getY() < bullet.getY() + 10 &&
            object.getY() + 50 > bullet.getY());
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
