/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-william.mallevays
** File description:
** Game.cpp
*/

#include "Game.hpp"
#include "Deserialization.hpp"


Game::Game() {
    _arcadeFont.loadFromFile("assets/Fonts/PublicPixel.ttf");
    _spaceShipTexture.loadFromFile("assets/Images/spaceShip.png");
    _spaceShip.setTexture(_spaceShipTexture);
    _spaceShipRect = {132, 0, 66, 34};
    _spaceShipPos = {100, 420};
    
    _count = 0;

    isRunning = false;

    _socket = std::make_shared<boost::asio::ip::udp::socket>(_service);
    _socket->open(boost::asio::ip::udp::v4());
}

Game::~Game() {
    _service.stop();
    if (isRunning) {
        isRunning = false;
        _thread.join();
    }
}

void Game::Display(const std::shared_ptr<sf::RenderWindow>& window) {
    _spaceShip.setTextureRect(_spaceShipRect);
    _spaceShip.setPosition(_spaceShipPos);
    window->draw(_spaceShip);
}

GameStatus Game::ManageInput(sf::Event event, std::string &serverIp) {
    if (!isRunning) {
        _serverIp = serverIp;
        isRunning = true;
        _thread = std::thread(&Game::connectToServer, this);
    }

    boost::array<unsigned char, 1> buf = {Actions::NONE};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        return GameStatus::MENU;

    if (sf::Keyboard::isKeyPressed(MOVE_LEFT) && _spaceShipPos.x > 0) {
        _spaceShipPos.x -= 4;
        buf = {Actions::LEFT};
    } else if (sf::Keyboard::isKeyPressed(MOVE_RIGHT) && _spaceShipPos.x < 1500 - 66) {
        _spaceShipPos.x += 4;
        buf = {Actions::RIGHT};
    } else if (sf::Keyboard::isKeyPressed(MOVE_UP) && _spaceShipPos.y > 0) {
        _spaceShipPos.y -= 4;
        _count++;
        if (_count >= 10)
            _spaceShipRect.left = 264;
        else
            _spaceShipRect.left = 198;
        buf = {Actions::UP};
    } else if (sf::Keyboard::isKeyPressed(MOVE_DOWN) && _spaceShipPos.y < 900 - 34) {
        _spaceShipPos.y += 4;
        _count++;
        if (_count >= 10)
            _spaceShipRect.left = 0;
        else
            _spaceShipRect.left = 66;
        buf = {Actions::DOWN};
    } else {
        _spaceShipRect.left = 132;
        _count = 0;
    }

    switch (event.key.code) {
        case sf::Keyboard::F1:
            _spaceShipRect.top = 0;
            break;
        case sf::Keyboard::F2:
            _spaceShipRect.top = 34;
            break;
        case sf::Keyboard::F3:
            _spaceShipRect.top = 68;
            break;
        case sf::Keyboard::F4:
            _spaceShipRect.top = 102;
            break;
        case sf::Keyboard::F5:
            _spaceShipRect.top = 136;
            break;
        default:
            break;
    }

    _socket->send_to(boost::asio::buffer(buf), _serverEndpoint);

    return GameStatus::GAME;
}

void Game::connectToServer() {
    _serverEndpoint = *boost::asio::ip::udp::resolver(_service).resolve({boost::asio::ip::udp::v4(), _serverIp, std::to_string(8080)});

    Network::Deseria deseria;

    while (isRunning)
    {
//        std::vector<float> send_vec = {_spaceShipPos.x, _spaceShipPos.y};
//        _socket->send_to(boost::asio::buffer(send_vec), _serverEndpoint);

//        boost::asio::deadline_timer timer(service, boost::posix_time::seconds(3));
//        timer.async_wait([&](const boost::system::error_code &error) {
//            if (error != boost::asio::error::operation_aborted) {
//                std::cout << "Disconnected from server (timeout)" << std::endl;
//                _isRunning = false;
//                return;
//            }
//        });

        boost::array<char, 1024> recv_buf{};
        boost::asio::ip::udp::endpoint sender_endpoint;
        size_t bytes_recvd = _socket->receive_from(boost::asio::buffer(recv_buf), sender_endpoint);

        std::cout << "Received message from " << sender_endpoint << ": ";
        std::pair<std::vector<Network::PlayerObject>, std::vector<Network::EnemyObject>> data = deseria.D_eserialize(recv_buf);
        for (auto &player : data.first) {
            std::cout << "Player " << player.getType() << " n°" << player.getPlayerNumber() << ", x=" << player.getX() << " y=" << player.getY() << std::endl;
        }


//        socket.async_receive_from(boost::asio::buffer(recv_buf), sender_endpoint, [&recv_buf, &sender_endpoint](const boost::system::error_code &ec, size_t bytes_recvd) {
//            if (ec) {
//                std::cout << "Error: " << ec.message() << std::endl;
//            } else {
//                std::cout << "Received message from " << sender_endpoint << ": ";
//                std::cout.write(recv_buf.data(), bytes_recvd);
//                std::cout << std::endl;
//            }
//        });
//
//        service.run();

//        std::this_thread::sleep_for(std::chrono::milliseconds(16));
//        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
}
