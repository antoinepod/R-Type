/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-william.mallevays
** File description:
** Game.cpp
*/

#include "Game.hpp"


Game::Game() {
    _spaceShip = LoadTexture("assets/spaceShip.png");
    _spaceShipPos = {100, 420};
    _spaceShipRec = {132, 0, 66, 34};
    _count = 0;

    _isRunning = false;
}

Game::~Game() {
    if (_isRunning) {
        _isRunning = false;
        _thread.join();
    }
}

void Game::Display() {
    ClearBackground(BLACK);
    DrawTextureRec(_spaceShip, _spaceShipRec, _spaceShipPos, WHITE);
}

GameStatus Game::ManageInput(std::string &serverIp) {
    if (!_isRunning) {
        _serverIp = serverIp;
        _isRunning = true;
        _thread = std::thread(&Game::connectToServer, this);
    }

    if (IsKeyPressed(KEY_ESCAPE))
        return GameStatus::MENU;

    if (IsKeyDown(KEY_UP) && _spaceShipPos.y > 0) {
        _spaceShipPos.y -= 4;
        _count++;
        if (_count >= 10)
            _spaceShipRec.x = 264;
        else
            _spaceShipRec.x = 198;
    } else if (IsKeyDown(KEY_DOWN) && _spaceShipPos.y < 900 - 34) {
        _spaceShipPos.y += 4;
        _count++;
        if (_count >= 10)
            _spaceShipRec.x = 0;
        else
            _spaceShipRec.x = 66;
    } else {
        _spaceShipRec.x = 132;
        _count = 0;
    }
    if (IsKeyDown(KEY_LEFT) && _spaceShipPos.x > 0) {
        _spaceShipPos.x -= 4;
    }
    if (IsKeyDown(KEY_RIGHT) && _spaceShipPos.x < 1500 - 66) {
        _spaceShipPos.x += 4;
    }

    if (IsKeyPressed(KEY_F1))
        _spaceShipRec.y = 0;
    if (IsKeyPressed(KEY_F2))
        _spaceShipRec.y = 34;
    if (IsKeyPressed(KEY_F3))
        _spaceShipRec.y = 68;
    if (IsKeyPressed(KEY_F4))
        _spaceShipRec.y = 102;
    if (IsKeyPressed(KEY_F5))
        _spaceShipRec.y = 136;

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
