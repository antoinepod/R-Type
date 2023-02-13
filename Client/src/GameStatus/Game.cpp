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

    _spaceShipTexture.emplace_back();
    _spaceShipTexture[0].loadFromFile("assets/Images/spaceShip.png");
    _spaceShip.emplace_back(_spaceShipTexture[0]);
    _spaceShipRect.emplace_back(132, 0, 66, 34);
    _spaceShip[0].setTextureRect(_spaceShipRect[0]);
    _spaceShipPos.emplace_back(100, 420);
    _spaceShip[0].setPosition(_spaceShipPos[0]);

    _spaceShipPos.emplace_back(100, 420);
    _spaceShipPos.emplace_back(100, 420);
    _spaceShipPos.emplace_back(100, 420);

    _count = 0;

    isRunning = false;

    _playerId = -2;

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
    for (int i = 0; i < _spaceShip.size(); i++) {
        _spaceShip[i].setTextureRect(_spaceShipRect[i]);
        _spaceShip[i].setPosition(_spaceShipPos[i]);
        window->draw(_spaceShip[i]);
    }
}

GameStatus Game::ManageInput(sf::Event event, std::string &serverIp) {
    std::cout << "player " << _playerId << std::endl;

    if (!isRunning) {
        _serverIp = serverIp;
        isRunning = true;
        _thread = std::thread(&Game::connectToServer, this);
    }

    boost::array<unsigned char, 1> buf = {Actions::NONE};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        return GameStatus::MENU;

    if (sf::Keyboard::isKeyPressed(MOVE_LEFT)) {
//        _spaceShipPos.x -= 4;
        buf = {Actions::LEFT};
    } else if (sf::Keyboard::isKeyPressed(MOVE_RIGHT)) {
//        _spaceShipPos.x += 4;
        buf = {Actions::RIGHT};
    } else if (sf::Keyboard::isKeyPressed(MOVE_UP)) {
//        _spaceShipPos.y -= 4;
        _count++;
        if (_count >= 10)
            _spaceShipRect[_playerId].left = 264;
        else
            _spaceShipRect[_playerId].left = 198;
        buf = {Actions::UP};
    } else if (sf::Keyboard::isKeyPressed(MOVE_DOWN)) {
//        _spaceShipPos.y += 4;
        _count++;
        if (_count >= 10)
            _spaceShipRect[_playerId].left = 0;
        else
            _spaceShipRect[_playerId].left = 66;
        buf = {Actions::DOWN};
    } else {
        _spaceShipRect[_playerId].left = 132;
        _count = 0;
    }

//    switch (event.key.code) {
//        case sf::Keyboard::F1:
//            _spaceShipRect.top = 0;
//            break;
//        case sf::Keyboard::F2:
//            _spaceShipRect.top = 34;
//            break;
//        case sf::Keyboard::F3:
//            _spaceShipRect.top = 68;
//            break;
//        case sf::Keyboard::F4:
//            _spaceShipRect.top = 102;
//            break;
//        case sf::Keyboard::F5:
//            _spaceShipRect.top = 136;
//            break;
//        default:
//            break;
//    }

      switch (_playerId) {
          case 1:
              _spaceShipRect[_playerId].top = 0;
              break;
          case 2:
              _spaceShipRect[_playerId].top = 34;
              break;
          case 3:
              _spaceShipRect[_playerId].top = 68;
              break;
          case 4:
              _spaceShipRect[_playerId].top = 102;
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
        std::vector<Network::Object> data = Network::Deseria::D_eserialize(recv_buf);
        while (_spaceShip.size() < data.size()) {
            int i = _spaceShip.size();
            _spaceShipTexture.emplace_back();
            _spaceShipTexture[i].loadFromFile("assets/Images/spaceShip.png");
            _spaceShip.emplace_back(_spaceShipTexture[i]);
            _spaceShipRect.emplace_back(132, 0, 66, 34);
            _spaceShip[i].setTextureRect(_spaceShipRect[i]);
            _spaceShip[i].setPosition(_spaceShipPos[i]);
        }
        for (auto &player : data) {
            std::cout << "Player " << player.getType() << " n°" << player.getId() << ", x=" << player.getX() << " y=" << player.getY() << std::endl;
            _spaceShipPos[player.getId()].x = player.getX();
            _spaceShipPos[player.getId()].y = player.getY();
        }
        if (_playerId < 0)
            _playerId++;
        if (_playerId == 0) {
            _playerId = data[data.size() - 1].getId();
            std::cout << "azerty " << _playerId << std::endl;
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
