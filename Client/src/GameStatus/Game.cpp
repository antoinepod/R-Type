/*
 EPITECH PROJECT, 2023
 B-CPP-500-LIL-5-2-rtype-william.mallevays
 File description:
 Game.cpp
*/

#include "Game.hpp"


Game::Game() {
    _input = {
        {UP, sf::Keyboard::Up},
        {DOWN, sf::Keyboard::Down},
        {LEFT, sf::Keyboard::Left},
        {RIGHT, sf::Keyboard::Right},
        {SHOOT, sf::Keyboard::Space}
    };

    _arcadeFont.loadFromFile("assets/Fonts/PublicPixel.ttf");

    // Player assets initialization
    _spaceShipTexture.loadFromFile("assets/Images/spaceShip.png");
    _spaceShip.setTexture(_spaceShipTexture);
    _spaceShipRect = {132, 0, 66, 34};
    _spaceShip.setTextureRect(_spaceShipRect);
    _spaceShip.setPosition(100, 420);

    // Bullet assets initialization
    _bulletTexture.loadFromFile("assets/Images/simpleBullet.png");
    _bullet.setTexture(_bulletTexture);

    _count = 0;

    isRunning = false;

    _playerId = 0;
    _canShoot = true;

    _socket = std::make_shared<boost::asio::ip::udp::socket>(_service);
    _socket->open(boost::asio::ip::udp::v4());
}

Game::~Game() {
    _service.stop();
    if (isRunning) {
        isRunning = false;
        for (auto & thread : _threads)
            thread.join();
    }
}

void Game::ShootTimer() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    _canShoot = true;
}

GameStatus Game::ManageInput(sf::Event event, std::string& serverIp, Inputs &inputs) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        return GameStatus::MENU;

    if (!isRunning) {
        _serverIp = serverIp;
        isRunning = true;
        _threads.emplace_back(&Game::ConnectToServer, this);
    }

    if (_playerId != 0) {
        boost::array<unsigned char, 1> buf = { Action::NONE };

        // Handle keyboard
        if (inputs.GetOK() && _canShoot) {
            _canShoot = false;
            buf = {Action::SHOOT};
            _threads.emplace_back(&Game::ShootTimer, this);
        } else if (inputs.GetUp())
            buf = {Action::UP};
        else if (inputs.GetDown())
            buf = {Action::DOWN};
        else if (inputs.GetLeft())
            buf = {Action::LEFT};
        else if (inputs.GetRight())
            buf = {Action::RIGHT};
        else
            buf = { Action::NONE };

        // Handle Joystick
        float x = sf::Joystick::getAxisPosition(0, sf::Joystick::PovX);
        float y = sf::Joystick::getAxisPosition(0, sf::Joystick::PovY);
        if (x == 0 && y == -100)
            buf = {Action::UP};
        if (x == 0 && y == 100)
            buf = {Action::DOWN};
        if (x == -100 && y == 0)
            buf = {Action::LEFT};
        if (x == 100 && y == 0)
            buf = {Action::RIGHT};
        if (sf::Joystick::isButtonPressed(0, 0) && _canShoot) {
            _canShoot = false;
            buf = {Action::SHOOT};
            _threads.emplace_back(&Game::ShootTimer, this);
        }

        _socket->send_to(boost::asio::buffer(buf), _serverEndpoint);
    }

    return GameStatus::GAME;
}

void Game::Display(const std::shared_ptr<sf::RenderWindow>& window) {
    for (auto & object : _objects) {
        switch (object.getType()) {
            case ObjectType::PLAYER:
                UpdatePlayer(object);
                window->draw(_spaceShip);
                break;
            case ENEMY:
                UpdateEnemy(object);
                break;
            case BULLET:
                UpdateBullet(object);
                window->draw(_bullet);
                break;
            case POWER_UP:
                UpdatePowerUp(object);
                break;
            default:
                break;
        }
    }
    _bullet.setPosition(100, 100);
    _bullet.setScale(2, 2);
    window->draw(_bullet);
}

void Game::UpdatePlayer(Network::Object & player) {
    switch (player.getId()) {
        case 1:
            _spaceShipRect.top = 0;
            break;
        case 2:
            _spaceShipRect.top = 34;
            break;
        case 3:
            _spaceShipRect.top = 68;
            break;
        case 4:
            _spaceShipRect.top = 102;
            break;
        default:
            break;
    }
    _spaceShip.setTextureRect(_spaceShipRect);
    _spaceShip.setPosition(player.getX(), player.getY());
}

void Game::UpdateEnemy(Network::Object &enemy) {
    // TODO
}

void Game::UpdateBullet(Network::Object &bullet) {
    _bullet.setPosition(bullet.getX(), bullet.getY());
}

void Game::UpdatePowerUp(Network::Object &powerUp) {
    // TODO
}

void Game::ConnectToServer() {
    try {
        boost::asio::ip::tcp::resolver resolver(_service);
        boost::asio::ip::tcp::resolver::query query(boost::asio::ip::tcp::v4(), _serverIp, std::to_string(12345));

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
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }


    _serverEndpoint = *boost::asio::ip::udp::resolver(_service).resolve({ boost::asio::ip::udp::v4(), _serverIp, std::to_string(8080) });
    _service.run();

    while (isRunning)
    {
        boost::array<char, 1024> recv_buf{};
        boost::asio::ip::udp::endpoint sender_endpoint;
        size_t bytes_recvd = _socket->receive_from(boost::asio::buffer(recv_buf), sender_endpoint);

        _objects = Network::Deseria::D_eserialize(recv_buf);

        // Debug
//        std::cout << "Received message from " << sender_endpoint << ": ";
//                for (auto& object : _objects) {
//            std::cout << "Object=" << object.getType() << " id=" << object.getId() << " x=" << object.getX() << " y=" << object.getY() << std::endl;
//        }
    }
}
