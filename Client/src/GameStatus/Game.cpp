/*
 EPITECH PROJECT, 2023
 B-CPP-500-LIL-5-2-rtype-william.mallevays
 File description:
 Game.cpp
*/

#include "Game.hpp"

#include <utility>


Game::Game() {
    _arcadeFont.loadFromFile("assets/Fonts/PublicPixel.ttf");

    _drawError = false;
    _errorText.setFont(_arcadeFont);
    _errorText.setCharacterSize(25);
    _errorText.setFillColor(sf::Color::Red);
    _errorText.setPosition(300, 400);

    // GameState assets initialization
    _gameStateText.setFont(_arcadeFont);
    _gameStateText.setCharacterSize(30);
    _gameStateText.setFillColor(sf::Color::White);
    _gameStateText.setPosition(300, 75);
    _helpText.setFont(_arcadeFont);
    _helpText.setCharacterSize(20);
    _helpText.setFillColor(sf::Color::White);
    _helpText.setPosition(300, 200);

    // Player assets initialization
    _spaceShipTexture.loadFromFile("assets/Images/spaceShip.png");
    _spaceShip.setTexture(_spaceShipTexture);
    _spaceShipRect = {132, 0, 66, 34};
    _spaceShip.setTextureRect(_spaceShipRect);
    _spaceShip.setPosition(100, 420);
    _playerName.setFont(_arcadeFont);
    _playerName.setCharacterSize(12);
    _playerName.setFillColor(sf::Color::White);
    _playerName.setPosition(90, 400);

    // Enemy assets initialization
    for (int i = 1; i<= 3; i++) {
        _enemyTextures[(EnemyType)(pow((double)EnemyType::ENEMY_1, i))] = std::make_shared<sf::Texture>();
        _enemyTextures[(EnemyType)(pow((double)EnemyType::ENEMY_1, i))]->loadFromFile("assets/Images/Enemies/Enemy" + std::to_string(i) + ".png");
        _enemies[(EnemyType)(pow((double)EnemyType::ENEMY_1, i))].setTexture(*_enemyTextures[(EnemyType)(pow((double)EnemyType::ENEMY_1, i))]);
    };
    _enemies[EnemyType::ENEMY_1].setScale(2, 2);
    _enemies[EnemyType::ENEMY_2].setScale(2, 2);
    _enemies[EnemyType::ENEMY_3].setScale(1.2, 1.2);
    // HealthBar assets initialization
    _healthBarTexture.loadFromFile("assets/Images/HealthBar.png");
    _healthBar.setTexture(_healthBarTexture);
    _healthBar.setScale(0.3, 0.3);
    _healthBar.setTextureRect({0, 0, 178, 37});

    // Bullet assets initialization
    for (int i = 1; i <= 3; i++) {
        _bulletTexture[(BulletType)(pow((double)BulletType::SIMPLE, i))] = std::make_shared<sf::Texture>();
        _bulletTexture[(BulletType)(pow((double)BulletType::SIMPLE, i))]->loadFromFile("assets/Images/Bullets/Bullet" + std::to_string(i) + ".png");
        _bullet[(BulletType)(pow((double)BulletType::SIMPLE, i))].setTexture(*_bulletTexture[(BulletType)(pow((double)BulletType::SIMPLE, i))]);
    }
    _canShoot[Action::SIMPLE_SHOOT] = true;
    _canShoot[Action::LASER_SHOOT] = true;
    _canShoot[Action::ROCKET_SHOOT] = true;

    // Explosion assets initialization
    _explosionRect[ExplosionType::MISSILE] = {0, 0, 16, 14};
    _explosionRect[ExplosionType::SMALL] = {0, 0, 32, 30};
    _explosionRect[ExplosionType::MEDIUM] = {0, 0, 32, 32};
    for (int i = 1; i <= 3; i++) {
        _explosionTexture[(ExplosionType) (pow((double)ExplosionType::MISSILE, i))] = std::make_shared<sf::Texture>();
        _explosionTexture[(ExplosionType) (pow((double)ExplosionType::MISSILE, i))]->loadFromFile("assets/Images/Explosions/Explosion" + std::to_string(i) + ".png");
        _explosion[(ExplosionType) (pow((double)ExplosionType::MISSILE, i))].setTexture(*_explosionTexture[(ExplosionType) (pow((double)ExplosionType::MISSILE, i))]);
        _explosion[(ExplosionType) (pow((double)ExplosionType::MISSILE, i))].setTextureRect(_explosionRect[(ExplosionType) (pow((double)ExplosionType::MISSILE, i))]);
//        _explosion[(ExplosionType) ((double)pow(ExplosionType::MISSILE, i))].setScale(4, 4);
    }
    _explosion[ExplosionType::MISSILE].setScale(6, 6);
    _explosion[ExplosionType::SMALL].setScale(2, 2);
    _explosion[ExplosionType::MEDIUM].setScale(3, 3);

    _playerId = 0;

    isRunning = false;
    _socket = std::make_shared<boost::asio::ip::udp::socket>(_service);
    _socket->open(boost::asio::ip::udp::v4());
    _socket->bind(boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 8082));
}

Game::~Game() {
    _service.stop();
    if (isRunning) {
        isRunning = false;
//        for (auto & thread : _threads)
//             thread.detach();
    }
}

void Game::ShootTimer(Action action) {
    switch (action) {
        case Action::SIMPLE_SHOOT:
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            break;
        case Action::LASER_SHOOT:
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            break;
        case Action::ROCKET_SHOOT:
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            break;
        default:
            break;
    }
    _canShoot[action] = true;
}

GameStatus Game::ManageInput(sf::Event event, std::string& serverIp, Inputs &inputs) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ||
    (event.type == sf::Event::JoystickButtonPressed && sf::Joystick::isButtonPressed(0, 1))) {
        isRunning = false;
        return GameStatus::MENU;
    }

    if (!isRunning) {
        _serverIp = serverIp;
        isRunning = true;
        _threads.emplace_back(&Game::ConnectToServer, this);
        _threads.back().detach();
    }

    if (_playerId != 0) {
        boost::array<unsigned int, 1> buf = { Action::NONE };

        // Handle keyboard
        buf = {(unsigned int)inputs.GetShoot()};
        if (buf[0] != Action::NONE && _canShoot[(Action)buf[0]]) {
            _canShoot[(Action)buf[0]] = false;
            _threads.emplace_back(&Game::ShootTimer, this, (Action)buf[0]);
            _threads.back().detach();
        } else {
            buf = {(unsigned int) inputs.GetAction()};
        }

        // Handle joystick
        float PovX = sf::Joystick::getAxisPosition(0, sf::Joystick::PovX);
        float PovY = sf::Joystick::getAxisPosition(0, sf::Joystick::PovY);
        float AxisX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
        float AxisY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
        if ((PovX == 0 && PovY == -100) || (AxisX > -100 && AxisX < 100 && AxisY < 0))
            buf = {Action::UP};
        if ((PovX == 0 && PovY == 100) || (AxisX > -100 && AxisX < 100 && AxisY > 0))
            buf = {Action::DOWN};
        if ((PovX == -100 && PovY == 0) || (AxisX < 0 && AxisY > -100 && AxisY < 100))
            buf = {Action::LEFT};
        if ((PovX == 100 && PovY == 0) || (AxisX > 0 && AxisY > -100 && AxisY < 100))
            buf = {Action::RIGHT};
        if (sf::Joystick::isButtonPressed(0, 0) && _canShoot[Action::SIMPLE_SHOOT]) {
            _canShoot[Action::SIMPLE_SHOOT] = false;
            buf = {Action::SIMPLE_SHOOT};
            _threads.emplace_back(&Game::ShootTimer, this, Action::SIMPLE_SHOOT);
            _threads.back().detach();
        } if (sf::Joystick::isButtonPressed(0, 3) && _canShoot[Action::LASER_SHOOT]) {
            _canShoot[Action::LASER_SHOOT] = false;
            buf = {Action::LASER_SHOOT};
            _threads.emplace_back(&Game::ShootTimer, this, Action::LASER_SHOOT);
            _threads.back().detach();
        } if (sf::Joystick::isButtonPressed(0, 2) && _canShoot[Action::ROCKET_SHOOT]) {
            _canShoot[Action::ROCKET_SHOOT] = false;
            buf = {Action::ROCKET_SHOOT};
            _threads.emplace_back(&Game::ShootTimer, this, Action::ROCKET_SHOOT);
            _threads.back().detach();
        }

        _socket->send_to(boost::asio::buffer(buf), _serverEndpoint);
    }

    return GameStatus::GAME;
}

void Game::Display(const std::shared_ptr<sf::RenderWindow>& window, const std::shared_ptr<Audio>& audio) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        audio->PlaySound(SoundType::EXPLOSION_MISSILE);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        audio->PlaySound(SoundType::EXPLOSION_SMALL);
    audio->StopMusic(MusicType::MENU_MUSIC);
    audio->PlayMusic(MusicType::GAME_MUSIC);
    if (_drawError) {
        _errorText.setString("Impossible to connect to " + _serverIp);
        window->draw(_errorText);
    } else {
        _mutex.lock();
        for (auto &object: _objects) {
            std::cout << "Object type: " << object.getType() << " position: " << object.getX() << " " << object.getY() << std::endl;
            switch (object.getType()) {
                case ObjectType::GAME_STATE:
                    UpdateGameState(window, object);
                    break;
                case ObjectType::PLAYER:
                    UpdatePlayer(window, object);
                    break;
                case ObjectType::ENEMY:
                    UpdateEnemy(window, object);
                    break;
                case ObjectType::BULLET:
                    UpdateBullet(window, object);
                    break;
                case ObjectType::POWER_UP:
                    UpdatePowerUp(window, object);
                    break;
                case ObjectType::EXPLOSION:
                    UpdateExplosion(window, object);
                    break;
                case ObjectType::SOUND:
                    UpdateSound(audio, object);
                    break;
                default:
                    break;
            }
        }
        _mutex.unlock();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
            std::cout << "LEVEL 1111111" << std::endl;
    }
}

void Game::UpdateGameState(const std::shared_ptr<sf::RenderWindow> &window, Network::Object &gameState) {
    switch (gameState.getGameState()) {
        case GameState::WAITING:
            _gameStateText.setString("Waiting for other players...");
            _helpText.setString("Press '1' to start Level 1, '2' to start Level 2, '3' to start Level 3");
            break;
        default:
            _gameStateText.setString("Work in progress");
            break;
    }

    Utils::HorizontalCenterText(_gameStateText, 75);
    Utils::HorizontalCenterText(_helpText, 200);
    window->draw(_gameStateText);
    window->draw(_helpText);
}

void Game::UpdatePlayer(const std::shared_ptr<sf::RenderWindow>& window, Network::Object & player) {
    _spaceShipRect.top = (player.getId() - 1) * 34;
    _spaceShipRect.left = 132 + (player.getFrame() * 66);

    _spaceShip.setTextureRect(_spaceShipRect);
    _spaceShip.setPosition(player.getX(), player.getY());

    _playerName.setString("Player " + std::to_string(player.getId()));
    _playerName.setPosition(player.getX() - 10, player.getY() - 20);
    if (player.getId() == _playerId)
        _playerName.setFillColor(sf::Color::White);

    window->draw(_playerName);
    window->draw(_spaceShip);
}

void Game::UpdateEnemy(const std::shared_ptr<sf::RenderWindow>& window, Network::Object & enemy) {
    EnemyType type = enemy.getEnemy();

    _enemies[type].setPosition(enemy.getX(), enemy.getY());

    int rectLeft = 712 - 178 * (enemy.getHealth() / 20 - 1);
    if (rectLeft > 712)
        rectLeft = 712;
    _healthBar.setTextureRect({rectLeft, 0, 178, 37});
    _healthBar.setPosition(enemy.getX(), enemy.getY() - 15);

    window->draw(_enemies[type]);
    window->draw(_healthBar);
}

void Game::UpdateBullet(const std::shared_ptr<sf::RenderWindow>& window, Network::Object & bullet) {
    BulletType type = bullet.getBullet();

    _bullet[type].setPosition(bullet.getX(), bullet.getY());

    window->draw(_bullet[type]);
}

void Game::UpdatePowerUp(const std::shared_ptr<sf::RenderWindow>& window, Network::Object & PowerUp) {
    // TODO
}

void Game::UpdateExplosion(const std::shared_ptr<sf::RenderWindow> & window, Network::Object & explosion) {
    ExplosionType type = explosion.getExplosion();

    _explosion[type].setPosition(explosion.getX(), explosion.getY());
    _explosionRect[type].left = explosion.getFrame() * _explosionRect[type].width;
    _explosion[type].setTextureRect(_explosionRect[type]);

    window->draw(_explosion[type]);
}

void Game::UpdateSound(const std::shared_ptr<Audio>& audio, Network::Object & sound) {
    if (sound.getId() == 1)
        audio->PlaySound(sound.getSound());
}

void Game::ConnectToServer() {
    try {
        boost::asio::ip::tcp::resolver resolver(_service);
        boost::asio::ip::tcp::resolver::query query(boost::asio::ip::tcp::v4(), _serverIp, std::to_string(8081));

        boost::asio::ip::tcp::socket socket(_service);
        boost::asio::connect(socket, resolver.resolve(query));

        char request[128] = "Hello, server!";
        boost::asio::write(socket, boost::asio::buffer(request, sizeof(request)));

        char response[128];
        boost::system::error_code error;
        size_t length = socket.read_some(boost::asio::buffer(response), error);

        if (error == boost::asio::error::eof) {
            std::cout << "Connection closed by server." << std::endl;
        }
        else if (error) {
            throw boost::system::system_error(error);
        }
        std::cout << "Response from server: " << response << std::endl;
        _playerId = response[0] - 88;
        std::cout << "Player ID = " << _playerId << std::endl;
        boost::asio::write(socket, boost::asio::buffer(request, sizeof(request)));
        _drawError = false;
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        _drawError = true;
    }

    try {
        _serverEndpoint = *boost::asio::ip::udp::resolver(_service).resolve({boost::asio::ip::udp::v4(), _serverIp, std::to_string(8080)});
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        _drawError = true;
    }
    _service.run();

    while (isRunning)
    {
        boost::array<char, 1024> recv_buf;
        boost::asio::ip::udp::endpoint sender_endpoint;
        size_t bytes_recvd = _socket->receive_from(boost::asio::buffer(recv_buf), sender_endpoint);

        UpdateData(Network::Deseria::D_eserialize(recv_buf));

        // Debug
//        std::cout << "Received message from " << sender_endpoint << ": ";
//                for (auto& object : _objects) {
//            std::cout << "Object=" << object.getType() << " id=" << object.getId() << " x=" << object.getX() << " y=" << object.getY() << std::endl;
//        }
    }
}

void Game::UpdateData(std::vector<Network::Object> objects) {
    _mutex.lock();
//    for (auto & object : objects) {
//        std::cout << "Object type: " << object.getType() << " position: " << object.getX() << " " << object.getY() << std::endl;
//    }
//    _objects.clear();
    _objects = std::move(objects);
    _mutex.unlock();
}
