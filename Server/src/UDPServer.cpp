/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** UDPServer.cpp
*/

#include "UDPServer.hpp"

UDPServer::UDPServer(boost::asio::io_context& io_context) : _socket(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 8080)) {
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
    _myMap = {};
}

UDPServer::~UDPServer() = default;

void UDPServer::StartReceive() {
    if (_recvBuffer.size() > 0) {
        _socket.async_receive_from(boost::asio::buffer(_recvBuffer), _remoteEndpoint, boost::bind(&UDPServer::Receive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)); {
            if (!_myMap.empty()) {
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

                    _gameObject[playerIndex].setGameState(GameState::WIN);

                    switch (_recvBuffer.data()[0]) {
                        case Action::SIMPLE_SHOOT:
                            if (_gameObject[playerIndex].getHealth() > 0) {
                                CreateBullet(_gameObject[playerIndex],
                                             BulletType::SIMPLE);
                            }
                            break;
                        case Action::LASER_SHOOT:
                            if (_gameObject[playerIndex].getHealth() > 0) {
                                CreateBullet(_gameObject[playerIndex],
                                             BulletType::LASER);
                            }
                            break;
                        case Action::ROCKET_SHOOT:
                            if (_gameObject[playerIndex].getHealth() > 0) {
                                CreateBullet(_gameObject[playerIndex],
                                             BulletType::ROCKET);
                            }
                            break;
                        case Action::LEFT:
                            if (_gameObject[playerIndex].getHealth() > 0) {
                                if (_gameObject[playerIndex].getX() > 0) {
                                    _gameObject[playerIndex].setX(
                                        _gameObject[playerIndex].getX() - 4);
                                    _playerFrames[search->second] = 0;
                                    _gameObject[playerIndex].setFrame(0);
                                }
                            }
                            break;
                        case Action::RIGHT:
                            if (_gameObject[playerIndex].getHealth() > 0) {
                                if (_gameObject[playerIndex].getX() <
                                    1500 - 66) {
                                    _gameObject[playerIndex].setX(
                                        _gameObject[playerIndex].getX() + 4);
                                    _playerFrames[search->second] = 0;
                                    _gameObject[playerIndex].setFrame(0);
                                }
                            }
                            break;
                        case Action::UP:
                            if (_gameObject[playerIndex].getHealth() > 0) {
                                if (_gameObject[playerIndex].getY() > 0) {
                                    _gameObject[playerIndex].setY(
                                        _gameObject[playerIndex].getY() - 4);
                                    _playerFrames[search->second]++;
                                    if (_playerFrames[search->second] >= 10)
                                        _gameObject[playerIndex].setFrame(2);
                                    else
                                        _gameObject[playerIndex].setFrame(1);
                                }
                            }
                            break;
                        case Action::DOWN:
                            if (_gameObject[playerIndex].getHealth() > 0) {
                                if (_gameObject[playerIndex].getY() <
                                    900 - 34) {
                                    _gameObject[playerIndex].setY(
                                        _gameObject[playerIndex].getY() + 4);
                                    _playerFrames[search->second]++;
                                    if (_playerFrames[search->second] >= 10)
                                        _gameObject[playerIndex].setFrame(-2);
                                    else
                                        _gameObject[playerIndex].setFrame(-1);
                                }
                            }
                            break;
                        case Action::NONE:
                            _playerFrames[search->second] = 0;
                            _gameObject[playerIndex].setFrame(0);
                            break;
                        case Action::LEVEL1:
                            Level_1(_gameObject.front());
                            break;
                        case Action::LEVEL2:
                            Level_2(_gameObject.front());
                            break;
                        case Action::LEVEL3:
                            Level_3(_gameObject.front());
                            break;
                        case Action::DISCONNECT:
                            _gameObject[playerIndex].setGameState(
                                GameState::WAITING);
                            std::cout
                                << "Client " + std::to_string(search->second) +
                                   " (" +
                                   _remoteEndpoint.address().to_string() +
                                   ") disconnected" << std::endl;
                            break;
                    }
                    _mutex.unlock();
                }
            }
        }
    }
}


void UDPServer::Receive(const boost::system::error_code& error, std::size_t) {
    if (!error) {
        _mutex.lock();
        Network::Seria::S_erialize(_gameObject, &_buf);
        _mutex.unlock();
        if (_buf.size() != 0) {
            std::string strBuf(boost::asio::buffers_begin(_buf.data()), boost::asio::buffers_end(_buf.data()));
            boost::shared_ptr<std::string> message(new std::string(strBuf));
            _socket.async_send_to(boost::asio::buffer(*message), _remoteEndpoint, boost::bind(&UDPServer::Send, this, message, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
            _buf.consume(_buf.size());
            StartReceive();
        }
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
    gameState.setId(0);
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
            object.setHealth(300);
            object.setId(id);
            object.setType(ObjectType::PLAYER);
            object.setFrame(0);
            object.setStrength(10);
            object.setBullet(BulletType::SIMPLE);
            object.setExplosion(ExplosionType::SMALL);
            object.setFullHealth(300);
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
    player.setExplosion(ExplosionType::SMALL);
    player.setFullHealth(300);

    _myMap.insert(std::pair<std::string, int>(ip, id));

    _mutex.lock();
    _gameObject.push_back(player);
    _mutex.unlock();
}

void UDPServer::CreateBullet(Network::Object sender, BulletType bulletType) {
    float celerity = 15;
    if (sender.getType() == ObjectType::ENEMY)
        celerity = -15;

    int strength = 0;
    switch (bulletType) {
        case BulletType::SIMPLE:
            CreateSound(SoundType::SHOOT_SIMPLE);
            strength = 25;
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
            object.setCelerity(celerity);
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
    bullet.setCelerity(celerity);
    bullet.setType(ObjectType::BULLET);
    bullet.setId(_bulletId++);
    bullet.setStrength(strength);
    bullet.setBullet(bulletType);
    bullet.setExplosion(ExplosionType::MISSILE);

    _gameObject.push_back(bullet);
}

void UDPServer::CreateEnemy(EnemyType type, float x, float y) {
    _nbEnemy++;

    float celerity = 0;
    int health = 0;
    BulletType bullet;
    ExplosionType explosion;
    switch (type) {
        case EnemyType::ENEMY_1:
            health = 100;
            celerity = 2;
            bullet = BulletType::SIMPLE;
            explosion = ExplosionType::SMALL;
            break;
        case EnemyType::ENEMY_2:
            health = 225;
            celerity = 1.5;
            bullet = BulletType::SIMPLE;
            explosion = ExplosionType::SMALL;
            break;
        case EnemyType::ENEMY_3:
            health = 350;
            celerity = 2.5;
            bullet = BulletType::SIMPLE;
            explosion = ExplosionType::SMALL;
            break;
        case EnemyType::BOSS_1:
            health = 1200;
            celerity = 1.5;
            bullet = BulletType::LASER;
            explosion = ExplosionType::BIG;
            break;
        case EnemyType::BOSS_2:
            health = 1600;
            celerity = 2;
            bullet = BulletType::ROCKET;
            explosion = ExplosionType::BIG;
            break;
        case EnemyType::BOSS_3:
            health = 2000;
            celerity = 2.5;
            bullet = BulletType::ROCKET;
            explosion = ExplosionType::BIG;
            break;
    }

    for (auto & object: _gameObject) {
        if (object.getType() == ObjectType::UNDEFINED) {
            object.setX(x);
            object.setY(y);
            object.setCelerity(celerity);
            object.setHealth(health);
            object.setType(ObjectType::ENEMY);
            object.setExplosion(explosion);
            object.setBullet(bullet);
            object.setEnemy(type);
            object.setFrame(rand() % 4);
            object.setFullHealth(health);
            return;
        }
    }

    Network::Enemy enemy;
    enemy.setX(x);
    enemy.setY(y);
    enemy.setCelerity(celerity);
    enemy.setHealth(health);
    enemy.setType(ObjectType::ENEMY);
    enemy.setExplosion(explosion);
    enemy.setBullet(bullet);
    enemy.setEnemy(type);
    enemy.setFrame(rand() % 4);
    enemy.setFullHealth(health);
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
            x -= 15;
            y -= 15;
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
    int nbPlayer = 0;
    int deadPlayer = 0;

    while (true) {
        _mutex.lock();
        for (auto &object: _gameObject) {
            if (object.getType() < ObjectType::UNDEFINED || object.getType() > ObjectType::GAME_STATE)
                object.setType(ObjectType::UNDEFINED);
            // Debug
            //            std::cout << "Object: " << object.getType() << " id:" << object.getId() << " pos: " << object.getX() << " " << object.getY() << std::endl;
            switch (object.getType()) {
                case ObjectType::GAME_STATE:
                    UpdateGameState(object);
                    break;
                case ObjectType::PLAYER:
                    nbPlayer++;
                    if (object.getHealth() <= 0)
                        deadPlayer++;
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
        if (nbPlayer == deadPlayer && _gameObject.size() > 1)
            _gameObject.front().setGameState(GameState::LOOSE);
        _mutex.unlock();
        nbPlayer = 0;
        deadPlayer = 0;
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}

void UDPServer::UpdateEnemy(Network::Object & enemy) {
    float spawn, x_min, x_max, y_min, y_max;
    if (enemy.getEnemy() >= EnemyType::ENEMY_1 && enemy.getEnemy() <= EnemyType::ENEMY_3) {
        spawn = 1400;
        x_min = 500;
        x_max = spawn - 20;
        y_min = 50;
        y_max = 800;
    } else {
        spawn = 1250;
        x_min = 650;
        x_max = spawn - 20;
        y_min = 100;
        y_max = 650;
    }

    if (enemy.getX() > spawn)
        enemy.setX(enemy.getX() - enemy.getCelerity());
    else if (rand() % 200 == 0)
        enemy.setFrame(rand() % 4);
    else {
        switch (enemy.getFrame()) {
            case 0:
                if (enemy.getY() <= y_max)
                    enemy.setY(enemy.getY() + enemy.getCelerity());
                else
                    enemy.setFrame(rand() % 4);
                break;
            case 1:
                if (enemy.getY() >= y_min)
                    enemy.setY(enemy.getY() - enemy.getCelerity());
                else
                    enemy.setFrame(rand() % 4);
                break;
            case 2:
                if (enemy.getX() < x_max)
                    enemy.setX(enemy.getX() + enemy.getCelerity());
                else
                    enemy.setFrame(rand() % 4);
                break;
            case 3:
                if (enemy.getX() >= x_min)
                    enemy.setX(enemy.getX() - enemy.getCelerity());
                else
                    enemy.setFrame(rand() % 4);
                break;
        }
    }

    int prob = (1 / sqrt(enemy.getEnemy())) * 300;
    if (rand() % prob == 0) {
        if (enemy.getEnemy() == EnemyType::BOSS_3) {
            if (rand() % 2 == 0)
                CreateBullet(enemy, BulletType::LASER);
            else
                CreateBullet(enemy, BulletType::ROCKET);
        }
        else
            CreateBullet(enemy, enemy.getBullet());
    }
}

void UDPServer::UpdateBullet(Network::Object & bullet) {
    if (bullet.getX() > 0 && bullet.getX() < 1500)
        bullet.setX(bullet.getX() + bullet.getCelerity());
    else {
        bullet.setType(ObjectType::UNDEFINED);
        return;
    }

    for (auto & object: _gameObject) {
        if (object.getType() == ObjectType::ENEMY) {
            if (CheckCollision(object, bullet) && bullet.getCelerity() > 0) {
                if (bullet.getBullet() == BulletType::ROCKET)
                    CreateExplosion(ExplosionType::MISSILE, bullet.getX() - 30, bullet.getY() - 30);
                object.setHealth(object.getHealth() - bullet.getStrength());
                bullet.setType(ObjectType::UNDEFINED);
                if (object.getHealth() <= 0) {
                    CreateExplosion(object.getExplosion(), object.getX(), object.getY());
                    _nbEnemy--;
                    object.setType(ObjectType::UNDEFINED);
                }
            }
        } if (object.getType() == ObjectType::PLAYER && object.getHealth() > 0) {
            if (CheckCollision(object, bullet) && bullet.getCelerity() < 0) {
                if (bullet.getBullet() == BulletType::ROCKET)
                    CreateExplosion(ExplosionType::MISSILE, bullet.getX() - 10, bullet.getY() - 20);
                object.setHealth(object.getHealth() - bullet.getStrength());
                bullet.setType(ObjectType::UNDEFINED);
                if (object.getHealth() <= 0) {
                    CreateExplosion(object.getExplosion(), object.getX(), object.getY());
                    object.setX(20);
                    object.setY(20 * object.getId());
                }
            }
        }
    }
}

bool UDPServer::CheckCollision(Network::Object & object, Network::Object & bullet) {
    if (object.getType() == ObjectType::PLAYER) {
        return (object.getX() < bullet.getX() &&
                object.getX() + 30 > bullet.getX()
                && object.getY() < bullet.getY() + 10 &&
                object.getY() + 30 > bullet.getY());
    } else if (object.getType() == ObjectType::ENEMY) {
        if (object.getEnemy() >= EnemyType::ENEMY_1 && object.getEnemy() <= EnemyType::ENEMY_3) {
            return (object.getX() < bullet.getX() &&
                    object.getX() + 60 > bullet.getX()
                    && object.getY() < bullet.getY() + 10 &&
                    object.getY() + 60 > bullet.getY());
        } else if (object.getEnemy() == EnemyType::BOSS_1) {
            return (object.getX() < bullet.getX() &&
                    object.getX() + 180 > bullet.getX()
                    && object.getY() < bullet.getY() &&
                    object.getY() + 180 > bullet.getY());
        } else if (object.getEnemy() == EnemyType::BOSS_2) {
            return (object.getX() < bullet.getX() &&
                    object.getX() + 235 > bullet.getX()
                    && object.getY() < bullet.getY() &&
                    object.getY() + 235 > bullet.getY());
        } else {
            return (object.getX() < bullet.getX() &&
                    object.getX() + 250 > bullet.getX()
                    && object.getY() < bullet.getY() &&
                    object.getY() + 250 > bullet.getY());
        }
    } else
        return false;
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


// Level and waves management

void UDPServer::Level_1(Network::Object & gameState) {
    std::cout << "Level 1" << std::endl;

    for (auto & object : _gameObject) {
        if (object.getType() == ObjectType::PLAYER) {
            object.setHealth(object.getFullHealth());
            object.setX(100);
            object.setY(420);
        }
    }
    if (gameState.getGameState() == GameState::WAITING || gameState.getGameState() == GameState::WIN || gameState.getGameState() == GameState::LOOSE) {
        gameState.setId(0);
        gameState.setGameState(GameState::LEVEL_1);
    }
}

void UDPServer::Level_2(Network::Object & gameState) {
    std::cout << "Level 2" << std::endl;

    if (gameState.getGameState() == GameState::WAITING || gameState.getGameState() == GameState::WIN || gameState.getGameState() == GameState::LOOSE) {
        gameState.setId(0);
        gameState.setGameState(GameState::LEVEL_2);
    }
}

void UDPServer::Level_3(Network::Object & gameState) {
    std::cout << "Level 3" << std::endl;

    if (gameState.getGameState() == GameState::WAITING || gameState.getGameState() == GameState::WIN || gameState.getGameState() == GameState::LOOSE) {
        gameState.setId(0);
        gameState.setGameState(GameState::LEVEL_3);
    }
}

void UDPServer::UpdateGameState(Network::Object &gameState) {
    switch (gameState.getGameState()) {
        case GameState::LEVEL_1:
            UpdateLevel_1(gameState);
            break;
        case GameState::LEVEL_2:
            UpdateLevel_2(gameState);
            break;
        case GameState::LEVEL_3:
            UpdateLevel_3(gameState);
            break;
        default:
            break;
    }
}

void UDPServer::UpdateLevel_1(Network::Object & gameState) {
    int wave = gameState.getId();

    if (_nbEnemy == 0) {
        switch (wave) {
            case 0:
                gameState.setId(1);
                for (int i = 0; i < 3; i++)
                    CreateEnemy(EnemyType::ENEMY_1, 1350, rand() % 700 + 50);
                break;
            case 1:
                gameState.setId(2);
                CreateEnemy(EnemyType::ENEMY_1, 1350, rand() % 700 + 50);
                CreateEnemy(EnemyType::ENEMY_2, 1350, rand() % 700 + 50);
                break;
            case 2:
                gameState.setId(3);
                CreateEnemy(EnemyType::ENEMY_1, 1350, rand() % 700 + 50);
                CreateEnemy(EnemyType::ENEMY_2, 1350, rand() % 700 + 50);
                CreateEnemy(EnemyType::ENEMY_3, 1350, rand() % 700 + 50);
                break;
            case 3:
                gameState.setId(4);
                CreateEnemy(EnemyType::BOSS_1, 1350, rand() % 700 + 50);
                break;
            case 4:
                gameState.setId(0);
                gameState.setGameState(GameState::LEVEL_2);
                break;
            default:
                break;
        }
    }
}

void UDPServer::UpdateLevel_2(Network::Object & gameState) {
    int wave = gameState.getId();

    if (_nbEnemy == 0) {
        switch (wave) {
            case 0:
                gameState.setId(1);
                CreateEnemy(EnemyType::ENEMY_1, 1350, rand() % 700 + 50);
                CreateEnemy(EnemyType::ENEMY_1, 1350, rand() % 700 + 50);
                break;
            case 1:
                gameState.setId(2);
                CreateEnemy(EnemyType::ENEMY_1, 1350, rand() % 700 + 50);
                CreateEnemy(EnemyType::ENEMY_1, 1350, rand() % 700 + 50);
                CreateEnemy(EnemyType::ENEMY_2, 1350, rand() % 700 + 50);
                CreateEnemy(EnemyType::ENEMY_2, 1350, rand() % 700 + 50);
                break;
            case 2:
                gameState.setId(3);
                CreateEnemy(EnemyType::ENEMY_1, 1350, rand() % 700 + 50);
                CreateEnemy(EnemyType::ENEMY_1, 1350, rand() % 700 + 50);
                CreateEnemy(EnemyType::ENEMY_2, 1350, rand() % 700 + 50);
                CreateEnemy(EnemyType::ENEMY_2, 1350, rand() % 700 + 50);
                CreateEnemy(EnemyType::ENEMY_3, 1350, rand() % 700 + 50);
                CreateEnemy(EnemyType::ENEMY_3, 1350, rand() % 700 + 50);
                break;
            case 3:
                gameState.setId(4);
                CreateEnemy(EnemyType::BOSS_2, 1350, rand() % 700 + 50);
                break;
            case 4:
                gameState.setId(0);
                gameState.setGameState(GameState::LEVEL_3);
                break;
            default:
                break;
        }
    }
}

void UDPServer::UpdateLevel_3(Network::Object & gameState) {
    int wave = gameState.getId();

    if (_nbEnemy == 0) {
        switch (wave) {
            case 0:
                gameState.setId(1);
                CreateEnemy(EnemyType::ENEMY_1, 1350, rand() % 700 + 50);
                CreateEnemy(EnemyType::ENEMY_1, 1350, rand() % 700 + 50);
                break;
            case 1:
                gameState.setId(2);
                CreateEnemy(EnemyType::ENEMY_1, 1350, rand() % 700 + 50);
                CreateEnemy(EnemyType::ENEMY_1, 1350, rand() % 700 + 50);
                CreateEnemy(EnemyType::ENEMY_2, 1350, rand() % 700 + 50);
                CreateEnemy(EnemyType::ENEMY_2, 1350, rand() % 700 + 50);
                break;
            case 2:
                gameState.setId(3);
                CreateEnemy(EnemyType::ENEMY_1, 1350, rand() % 700 + 50);
                CreateEnemy(EnemyType::ENEMY_1, 1350, rand() % 700 + 50);
                CreateEnemy(EnemyType::ENEMY_2, 1350, rand() % 700 + 50);
                CreateEnemy(EnemyType::ENEMY_2, 1350, rand() % 700 + 50);
                CreateEnemy(EnemyType::ENEMY_3, 1350, rand() % 700 + 50);
                CreateEnemy(EnemyType::ENEMY_3, 1350, rand() % 700 + 50);
                break;
            case 3:
                gameState.setId(4);
                CreateEnemy(EnemyType::BOSS_3, 1350, rand() % 700 + 50);
                break;
            case 4:
                gameState.setId(0);
                gameState.setGameState(GameState::WIN);
                break;
            default:
                break;
        }
    }
}