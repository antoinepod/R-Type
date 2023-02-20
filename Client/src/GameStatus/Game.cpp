/*
 EPITECH PROJECT, 2023
 B-CPP-500-LIL-5-2-rtype-william.mallevays
 File description:
 Game.cpp
*/

#include "Game.hpp"


Game::Game() {
    _arcadeFont.loadFromFile("assets/Fonts/PublicPixel.ttf");

    _spaceShipTexture.loadFromFile("assets/Images/spaceShip.png");
    _spaceShip.setTexture(_spaceShipTexture);
    _spaceShip.setTextureRect(sf::IntRect(132, 0, 66, 34));
    _spaceShip.setPosition(100, 420);

    _count = 0;

    isRunning = false;

    _playerId = 0;

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
    _spaceShip.setPosition(10, 10);
    window->draw(_spaceShip);

    for (auto & _object : _objects) {
        if (_object.getType() == ObjectType::PLAYER) {
            _spaceShip.setPosition(_object.getX(), _object.getY());
            window->draw(_spaceShip);
        }
    }
}

GameStatus Game::ManageInput(sf::Event event, std::string& serverIp) {
    std::cout << "player " << _playerId << std::endl;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        return GameStatus::MENU;

    if (!isRunning) {
        _serverIp = serverIp;
        isRunning = true;
        _thread = std::thread(&Game::ConnectToServer, this);
    }

    if (_playerId != 0) {
        boost::array<unsigned char, 1> buf = { Actions::NONE };

        if (sf::Keyboard::isKeyPressed(MOVE_LEFT))
            buf = {Actions::LEFT};
        else if (sf::Keyboard::isKeyPressed(MOVE_RIGHT))
            //        _spaceShipPos.x += 4;
            buf = {Actions::RIGHT};
        else if (sf::Keyboard::isKeyPressed(MOVE_UP))
            buf = {Actions::UP};
        else if (sf::Keyboard::isKeyPressed(MOVE_DOWN))
            buf = {Actions::DOWN};
        else
            buf = { Actions::NONE };

        _socket->send_to(boost::asio::buffer(buf), _serverEndpoint);
    }

    return GameStatus::GAME;
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
        //        std::vector<float> send_vec = {_spaceShipPos.x, _spaceShipPos.y};
        //        _socket->send_to(boost::asio::buffer(send_vec), _serverEndpoint);

        //        boost::asio::deadline_timer timer(service, boost::posix_time::seconds(3));
        //        timer.async_wait(& {
        //            if (error != boost::asio::error::operation_aborted) {
        //                std::cout << "Disconnected from server (timeout)" << std::endl;
        //                _isRunning = false;
        //
        //                return;
        //            }
        //        });

        boost::array<char, 1024> recv_buf{};
        boost::asio::ip::udp::endpoint sender_endpoint;
        size_t bytes_recvd = _socket->receive_from(boost::asio::buffer(recv_buf), sender_endpoint);

        std::cout << "Received message from " << sender_endpoint << ": ";
        _objects = Network::Deseria::D_eserialize(recv_buf);

        for (auto& object : _objects) {
            std::cout << "Object=" << object.getType() << " id=" << object.getId() << " x=" << object.getX() << " y=" << object.getY() << std::endl;
        }

        //        while (_spaceShip.size() < data.size()) {
        //            int i = _spaceShip.size();
        //            _spaceShipTexture.emplace_back();
        //            _spaceShipTexture[i].loadFromFile("assets/Images/spaceShip.png");
        //            _spaceShip.emplace_back(_spaceShipTexture[i]);
        //            _spaceShipRect.emplace_back(132, 0, 66, 34);
        //            _spaceShip[i].setTextureRect(_spaceShipRect[i]);
        //            _spaceShip[i].setPosition(_spaceShipPos[i]);
        //        }
        //        for (auto& player : data) {
        //            std::cout << "Player " << player.getType() << " n°" << player.getId() << ", x=" << player.getX() << " y=" << player.getY() << std::endl;
        //            _spaceShipPos[player.getId()].x = player.getX();
        //            _spaceShipPos[player.getId()].y = player.getY();
        //        }


        //        socket.async_receive_from(boost::asio::buffer(recv_buf), sender_endpoint, &recv_buf, &sender_endpoint {
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