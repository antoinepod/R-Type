/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** UDPServer.cpp
*/


#include "UDPServer.hpp"


UDPServer::UDPServer(boost::asio::io_context& io_context) : socket_(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 8080)) {
    StartReceive();
    for (int i = 0; i < THREADS_NBR; i++) {
        threadPool.emplace_back(&UDPServer::StartReceive, this);
    }
}

UDPServer::~UDPServer() = default;

void UDPServer::StartReceive() {
    socket_.async_receive_from(boost::asio::buffer(recv_buffer_), remote_endpoint_,boost::bind(&UDPServer::Receive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    std::cout << "" << std::to_string(recv_buffer_.data()[0]) << std::endl;
    //std::cout << "" << remote_endpoint_.address().to_string() << std::endl;

    //        if (remote_endpoint_.address().to_string().compare("0.0.0.0") != 0) {

    //        auto search = myMap.find(remote_endpoint_.address().to_string() + std::to_string(remote_endpoint_.port()));
    auto search = myMap.find(remote_endpoint_.address().to_string());

    if ((myMap.empty() || search == myMap.end())) {
        //if (remote_endpoint_.address().to_string() != "0.0.0.0") {
        gameObject.push_back(Network::Populate::Player(p_Id, 100, 420));
        myMap[remote_endpoint_.address().to_string()] = p_Id;
        p_Id += 1;
        //}
    }

    //if (remote_endpoint_.address().to_string() != "0.0.0.0") {
    for (auto& i : myMap)
        std::cout << i.first << "  " << i.second << std::endl;
    //if (!remote_endpoint_.address().to_string().compare("127.0.0.1"))
    //        myMap[remote_endpoint_.address().to_string() + std::to_string(remote_endpoint_.port())] = p_Id;

    switch (recv_buffer_.data()[0]) {
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

        //if (recv_buffer_.data()[0] == static_cast<unsigned char>(RType::Events::QUIT)) {
        //    myMap.erase(remote_endpoint_.address().to_string());
        //    if (myMap.size() == 0) {
        //        for (auto& t : threadPool)
        //            t.join();
        //        return;
        //    }
        //}
        //        }
}


void UDPServer::Receive(const boost::system::error_code& error, std::size_t) {
    if (!error) {
        Network::Seria::S_erialize(gameObject, &buf);
        std::string strBuf(boost::asio::buffers_begin(buf.data()),boost::asio::buffers_end(buf.data()));
        boost::shared_ptr<std::string> message(new std::string(strBuf));
        //            std::cout << "" << *message << std::endl;
        //std::cout << "Serialized data size: " << buf.size() << "and mess length: " << message->length() << std::endl;
        socket_.async_send_to(boost::asio::buffer(*message), remote_endpoint_, boost::bind(&UDPServer::Send, this, message, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
        buf.consume(buf.size());
        StartReceive();
    }
}

void UDPServer::Send(boost::shared_ptr<std::string>,const boost::system::error_code&,std::size_t) {
    return;
}
