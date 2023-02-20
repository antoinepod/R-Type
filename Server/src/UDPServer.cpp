/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** UDPServer.cpp
*/


#include "UDPServer.hpp"


UDPServer::UDPServer(boost::asio::io_context& io_context) : _socket(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 8080)) {
    StartReceive();
    for (int i = 0; i < THREADS_NBR; i++) {
        _threadPool.emplace_back(&UDPServer::StartReceive, this);
    }
}

UDPServer::~UDPServer() = default;

void UDPServer::StartReceive() {
    _socket.async_receive_from(boost::asio::buffer(_recvBuffer), _remoteEndpoint,boost::bind(&UDPServer::Receive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    std::cout << _remoteEndpoint.address().to_string() << ": " << std::to_string(_recvBuffer.data()[0]) << std::endl;

    auto search = _myMap.find(_remoteEndpoint.address().to_string());

    if (!_myMap.empty() && search != _myMap.end()) {

        for (auto &i: _myMap)
            std::cout << i.first << "  " << i.second << std::endl;

        switch (_recvBuffer.data()[0]) {
            case Actions::LEFT:
                if (gameObject[search->second - 1].getX() > 0)
                    gameObject[search->second - 1].setX(gameObject[search->second - 1].getX() - 4);
                break;
            case Actions::RIGHT:
                if (gameObject[search->second - 1].getX() < 1500 - 66)
                    gameObject[search->second - 1].setX(gameObject[search->second - 1].getX() + 4);
                break;
            case Actions::UP:
                if (gameObject[search->second - 1].getY() > 0)
                    gameObject[search->second - 1].setY(gameObject[search->second - 1].getY() - 4);
                break;
            case Actions::DOWN:
                if (gameObject[search->second - 1].getY() < 900 - 34)
                    gameObject[search->second - 1].setY(gameObject[search->second - 1].getY() + 4);
                break;
        }
        //}

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
}


void UDPServer::Receive(const boost::system::error_code& error, std::size_t) {
    if (!error) {
        Network::Seria::S_erialize(gameObject, &_buf);
        std::string strBuf(boost::asio::buffers_begin(_buf.data()),boost::asio::buffers_end(_buf.data()));
        boost::shared_ptr<std::string> message(new std::string(strBuf));
        //            std::cout << "" << *message << std::endl;
        //std::cout << "Serialized data size: " << _buf.size() << "and mess length: " << message->length() << std::endl;
        _socket.async_send_to(boost::asio::buffer(*message), _remoteEndpoint, boost::bind(&UDPServer::Send, this, message, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
        _buf.consume(_buf.size());
        StartReceive();
    }
}

void UDPServer::Send(boost::shared_ptr<std::string>, const boost::system::error_code&,std::size_t) {}

void UDPServer::CreateNewPlayer(const std::string& ip, int id) {
    gameObject.push_back(Network::Populate::Player(id, 100, 420));
    _myMap.insert(std::pair<std::string, int>(ip, id));
}
