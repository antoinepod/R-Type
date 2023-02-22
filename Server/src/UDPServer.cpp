/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** UDPServer.cpp
*/

#include "UDPServer.hpp"


UDPServer::UDPServer(boost::asio::io_context& io_context) : _socket(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 8080)) {
    _timer = std::make_shared<boost::asio::deadline_timer>(io_context, boost::posix_time::milliseconds(16));
    StartReceive();
    for (int i = 0; i < THREADS_NBR; i++) {
        _threadPool.emplace_back(&UDPServer::StartReceive, this);
    }
}

UDPServer::~UDPServer() = default;

void UDPServer::StartReceive() {
    _timer->async_wait(boost::bind(&UDPServer::UpdateGame, this));
    _socket.async_receive_from(boost::asio::buffer(_recvBuffer), _remoteEndpoint,boost::bind(&UDPServer::Receive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    // Debug
    // std::cout << _remoteEndpoint.address().to_string() << ": " << std::to_string(_recvBuffer.data()[0]) << std::endl;

    auto search = _myMap.find(_remoteEndpoint.address().to_string());
    if (!_myMap.empty() && search != _myMap.end()) {
        // Debug
        // for (auto &i: _myMap)
        //     std::cout << i.first << "  " << i.second << std::endl;

        int playerIndex = FindPlayer(search->second);

        switch (_recvBuffer.data()[0]) {
            case Action::SHOOT:
                CreateBullet(_gameObject[playerIndex], _gameObject[playerIndex].getX(), _gameObject[playerIndex].getY());
                break;
            case Action::LEFT:
                if (_gameObject[playerIndex].getX() > 0)
                    _gameObject[playerIndex].setX(_gameObject[playerIndex].getX() - 4);
                break;
            case Action::RIGHT:
                if (_gameObject[playerIndex].getX() < 1500 - 66)
                    _gameObject[playerIndex].setX(_gameObject[playerIndex].getX() + 4);
                break;
            case Action::UP:
                if (_gameObject[playerIndex].getY() > 0)
                    _gameObject[playerIndex].setY(_gameObject[playerIndex].getY() - 4);
                break;
            case Action::DOWN:
                if (_gameObject[playerIndex].getY() < 900 - 34)
                    _gameObject[playerIndex].setY(_gameObject[playerIndex].getY() + 4);
                break;
        }

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
//    for (auto & object : _gameObject) {
//        if (object.getType() == ObjectType::BULLET) {
//            if (object.getX() > 1500 || object.getX() < 0 || object.getY() > 900 || object.getY() < 0) {
//                object.setX(object.getX() + object.getCelerity());
//            }
//        }
//    }
}


void UDPServer::Receive(const boost::system::error_code& error, std::size_t) {
    if (!error) {
//        if (_gameObject.size() > 1)
//            _gameObject[1].setX(_gameObject[1].getX() + _gameObject[1].getCelerity());
        Network::Seria::S_erialize(_gameObject, &_buf);
        std::string strBuf(boost::asio::buffers_begin(_buf.data()),boost::asio::buffers_end(_buf.data()));
        boost::shared_ptr<std::string> message(new std::string(strBuf));
        //            std::cout << "" << *message << std::endl;
        //std::cout << "Serialized data size: " << _buf.size() << "and mess length: " << message->length() << std::endl;
        _socket.async_send_to(boost::asio::buffer(*message), _remoteEndpoint, boost::bind(&UDPServer::Send, this, message, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
        _buf.consume(_buf.size());
        StartReceive();
    }
}

void UDPServer::UpdateGame() {
    for (auto & object : _gameObject) {
//        std::cout << "Object: " << object->getType() << " pos: " << object->getX() << " " << object->getY() << std::endl;
        if (object.getId() != -1 && object.getType() == ObjectType::BULLET) {
            if (object.getX() > 0 && object.getX() < 1500)
                object.setX(object.getX() + object.getCelerity());
            else {
                object.setId(-1);
            }
        }
    }

//    for (auto it = _gameObject.begin(); it != _gameObject.end(); it++) {
//        if (it->getType() == ObjectType::BULLET && it->getId() == -1)
//            _gameObject.erase(it);
//    }
}

int UDPServer::FindPlayer(int id) {
    for (int i = 0; i < _gameObject.size(); i++) {
        if (_gameObject[i].getType() == ObjectType::PLAYER && _gameObject[i].getId() == id)
            return i;
    }
    return -1;
}

void UDPServer::Send(boost::shared_ptr<std::string>, const boost::system::error_code&,std::size_t) {}

void UDPServer::CreatePlayer(const std::string& ip, int id) {
    Network::Player player;
    player.setX(100);
    player.setY(420);
    player.setCelerity(4);
    player.setHealth(200);
    player.setId(id);
    player.setType(ObjectType::PLAYER);
    _gameObject.push_back(player);

    _myMap.insert(std::pair<std::string, int>(ip, id));
}

void UDPServer::CreateBullet(Network::Object & sender, float x, float y) {
    Network::Bullet bullet;
    bullet.setX(x);
    bullet.setY(y);
    bullet.setCelerity(8);
    bullet.setType(ObjectType::BULLET);
    bullet.setId(0);
    _gameObject.push_back(bullet);
}
