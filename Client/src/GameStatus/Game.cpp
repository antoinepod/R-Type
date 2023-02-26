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

    // Player assets initialization
    _spaceShipTexture.loadFromFile("assets/Images/spaceShip.png");
    _spaceShip.setTexture(_spaceShipTexture);
    _spaceShipRect = {132, 0, 66, 34};
    _spaceShip.setTextureRect(_spaceShipRect);
    _spaceShip.setPosition(100, 420);

    // Bullet assets initialization
    _bulletTexture.loadFromFile("assets/Images/simpleBullet.png");
    _bullet.setTexture(_bulletTexture);
    _bullet.setScale(2, 2);

    // TODO
     _playerName.setFont(_arcadeFont);
     _playerName.setCharacterSize(12);
     _playerName.setFillColor(sf::Color::White);
     _playerName.setPosition(90, 400);

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
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    _canShoot = true;
}

GameStatus Game::ManageInput(sf::Event event, std::string& serverIp, Inputs &inputs) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        return GameStatus::MENU;
    if (event.type == sf::Event::JoystickButtonPressed && sf::Joystick::isButtonPressed(0, 1))
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
    _mutex.lock();
    for (auto & object : _objects) {
        std::cout << "Object type: " << object.getType() << " position: " << object.getX() << " " << object.getY() << std::endl;
        switch (object.getType()) {
            case ObjectType::PLAYER:
                UpdatePlayer(window, object);
                break;
            case ENEMY:
                UpdateEnemy(window, object);
                break;
            case BULLET:
                UpdateBullet(window, object);
                break;
            case POWER_UP:
                UpdatePowerUp(window, object);
                break;
            default:
                break;
        }
    }
    _mutex.unlock();
}

void Game::UpdatePlayer(const std::shared_ptr<sf::RenderWindow>& window, Network::Object & player) {
    _spaceShipRect.top = (player.getId() - 1) * 34;
    _spaceShipRect.left = 132 + (player.getFrame() * 66);

    _spaceShip.setTextureRect(_spaceShipRect);
    _spaceShip.setPosition(player.getX(), player.getY());

    _playerName.setString("Player " + std::to_string(_playerId));
    _playerName.setPosition(player.getX() - 10, player.getY() - 20);
    if (player.getId() == _playerId)
        _playerName.setFillColor(sf::Color::White);

    window->draw(_playerName);
    window->draw(_spaceShip);
}

void Game::UpdateEnemy(const std::shared_ptr<sf::RenderWindow>& window, Network::Object & enemy) {
    // TODO
}

void Game::UpdateBullet(const std::shared_ptr<sf::RenderWindow>& window, Network::Object & bullet) {
    _bullet.setPosition(bullet.getX(), bullet.getY());

    window->draw(_bullet);
}

void Game::UpdatePowerUp(const std::shared_ptr<sf::RenderWindow>& window, Network::Object & powerUp) {
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
        boost::asio::write(socket, boost::asio::buffer(request, sizeof(request)));
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
