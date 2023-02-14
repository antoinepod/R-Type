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
    std::cout << "" << std::to_string(_recvBuffer.data()[0]) << std::endl;
    //std::cout << "" << _remoteEndpoint.address().to_string() << std::endl;

    //        if (_remoteEndpoint.address().to_string().compare("0.0.0.0") != 0) {

    //        auto search = _myMap.find(_remoteEndpoint.address().to_string() + std::to_string(_remoteEndpoint.port()));
    auto search = _myMap.find(_remoteEndpoint.address().to_string());

    if ((_myMap.empty() || search == _myMap.end())) {
        //if (_remoteEndpoint.address().to_string() != "0.0.0.0") {
        gameObject.push_back(Network::Populate::Player(p_Id, 100, 420));
        _myMap[_remoteEndpoint.address().to_string()] = p_Id;
        p_Id += 1;
        //}
    }

    //if (_remoteEndpoint.address().to_string() != "0.0.0.0") {
    for (auto& i : _myMap)
        std::cout << i.first << "  " << i.second << std::endl;
    //if (!_remoteEndpoint.address().to_string().compare("127.0.0.1"))
    //        _myMap[_remoteEndpoint.address().to_string() + std::to_string(_remoteEndpoint.port())] = p_Id;

    switch (_recvBuffer.data()[0]) {
        case RType::Actions::LEFT:
            if (gameObject[search->second].getX() > 0)
                gameObject[search->second].setX(
                    gameObject[search->second].getX() - 4);
            break;
        case RType::Actions::RIGHT:
            if (gameObject[search->second].getX() < 1500 - 66)
                gameObject[search->second].setX(
                    gameObject[search->second].getX() + 4);
            break;
        case RType::Actions::UP:
            if (gameObject[search->second].getY() > 0)
                gameObject[search->second].setY(
                    gameObject[search->second].getY() - 4);
            break;
        case RType::Actions::DOWN:
            if (gameObject[search->second].getY() < 900 - 34)
                gameObject[search->second].setY(
                    gameObject[search->second].getY() + 4);
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
