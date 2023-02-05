/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-william.mallevays
** File description:
** Game.cpp
*/

#include "Game.hpp"


Game::Game() {
    if (!_arcadeFont.loadFromFile("../../Client/assets/Fonts/PublicPixel.ttf")) {
        std::cerr << "Failed to load '../../Client/assets/Fonts/PublicPixel.ttf'" << std::endl;
        //exit(84);
    }

    if (!_spaceShipTexture.loadFromFile("../../Client/assets/Images/spaceShip.png")) {
        std::cerr << "Failed to load 'assets/spaceShip.png'" << std::endl;
        //exit(84);
    }
    _spaceShip.setTexture(_spaceShipTexture);
    _spaceShipRect = {132, 0, 66, 34};
    _spaceShipPos = {100, 420};
    
    _count = 0;
    _isRunning = false;
}

Game::~Game() {
    if (_isRunning) {
        _isRunning = false;
        _thread.join();
    }
}

void Game::Display(const std::shared_ptr<sf::RenderWindow>& window) {
    _spaceShip.setTextureRect(_spaceShipRect);
    _spaceShip.setPosition(_spaceShipPos);
    window->draw(_spaceShip);
}

GameStatus Game::ManageInput(sf::Event event, std::string &serverIp) {
    if (!_isRunning) {
        _serverIp = serverIp;
        _isRunning = true;
        _thread = std::thread(&Game::connectToServer, this);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        return GameStatus::MENU;

    if (sf::Keyboard::isKeyPressed(UP) && _spaceShipPos.y > 0) {
        _spaceShipPos.y -= 4;
        _count++;
        if (_count >= 10)
            _spaceShipRect.left = 264;
        else
            _spaceShipRect.left = 198;
    } else if (sf::Keyboard::isKeyPressed(DOWN) && _spaceShipPos.y < 900 - 34) {
        _spaceShipPos.y += 4;
        _count++;
        if (_count >= 10)
            _spaceShipRect.left = 0;
        else
            _spaceShipRect.left = 66;
    } else {
        _spaceShipRect.left = 132;
        _count = 0;
    }

    if (sf::Keyboard::isKeyPressed(LEFT) && _spaceShipPos.x > 0)
        _spaceShipPos.x -= 4;
    if (sf::Keyboard::isKeyPressed(RIGHT) && _spaceShipPos.x < 1500 - 66)
        _spaceShipPos.x += 4;

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

    return GameStatus::GAME;
}

void Game::connectToServer() {
    boost::asio::io_service service;
    boost::asio::ip::udp::socket socket(service);
    socket.open(boost::asio::ip::udp::v4());
    boost::asio::ip::udp::endpoint server_endpoint = *boost::asio::ip::udp::resolver(service).resolve({boost::asio::ip::udp::v4(), _serverIp, std::to_string(8080)});

    while (_isRunning)
    {
        std::vector<float> send_vec = {_spaceShipPos.x, _spaceShipPos.y};
        socket.send_to(boost::asio::buffer(send_vec), server_endpoint);

//        boost::asio::deadline_timer timer(service, boost::posix_time::seconds(3));
//        timer.async_wait([&](const boost::system::error_code &error) {
//            if (error != boost::asio::error::operation_aborted) {
//                std::cout << "Disconnected from server (timeout)" << std::endl;
//                _isRunning = false;
//                return;
//            }
//        });

        std::array<char, 1024> recv_buf{};
        boost::asio::ip::udp::endpoint sender_endpoint;
        size_t bytes_recvd = socket.receive_from(boost::asio::buffer(recv_buf), sender_endpoint);

        std::cout << "Received message from " << sender_endpoint << ": ";
        std::cout.write(recv_buf.data(), bytes_recvd);
        std::cout << std::endl;

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
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
}
