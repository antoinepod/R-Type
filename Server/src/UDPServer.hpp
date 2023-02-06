/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** UDPServer.cpp
*/

#pragma once

#include "Serialization.hpp"
#include "Deserialization.hpp"

class udp_server
{
public:
    udp_server(boost::asio::io_context& io_context)
        : socket_(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 8080))
    {
        start_receive();
        for (int i = 0; i < THREADS_NBR; i++) {
            threadPool.emplace_back(&udp_server::start_receive, this);
        }
    }


    std::vector<Network::GameObject> gameObject;
//    std::pair<std::vector<Network::PlayerObject>, std::vector<Network::EnemyObject>> gameObject;

private:
    int p_Id = -1;

    void start_receive()
    {
        socket_.async_receive_from(boost::asio::buffer(recv_buffer_), remote_endpoint_,boost::bind(&udp_server::handle_receive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
        std::cout << "" << std::to_string(recv_buffer_.data()[0]) << std::endl;
        //std::cout << "" << remote_endpoint_.address().to_string() << std::endl;

//        if (remote_endpoint_.address().to_string().compare("0.0.0.0") != 0) {

            //        auto search = myMap.find(remote_endpoint_.address().to_string() + std::to_string(remote_endpoint_.port()));
            auto search = myMap.find(remote_endpoint_.address().to_string());

            if ((myMap.empty() || search == myMap.end())) {
                p_Id++;
                gameObject.push_back(
                    Network::Populate::PlayerObject(p_Id, 100, 420));
            }
            //if (!remote_endpoint_.address().to_string().compare("127.0.0.1"))
            //        myMap[remote_endpoint_.address().to_string() + std::to_string(remote_endpoint_.port())] = p_Id;
            myMap[remote_endpoint_.address().to_string()] = p_Id;

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

    void handle_receive(const boost::system::error_code& error,std::size_t)
    {
        if (!error)
        {
            Network::Seria::S_erialize(gameObject, &buf);
            std::string strBuf(boost::asio::buffers_begin(buf.data()),boost::asio::buffers_end(buf.data()));
            boost::shared_ptr<std::string> message(new std::string(strBuf));
//            std::cout << "" << *message << std::endl;
            //std::cout << "Serialized data size: " << buf.size() << "and mess length: " << message->length() << std::endl;
            socket_.async_send_to(boost::asio::buffer(*message), remote_endpoint_, boost::bind(&udp_server::handle_send, this, message, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
            buf.consume(buf.size());
            start_receive();
        }
    }

    void handle_send(boost::shared_ptr<std::string>,const boost::system::error_code&,std::size_t){}

    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint remote_endpoint_;
    //boost::asio::io_context& _io_context;
    boost::array<unsigned char, 1> recv_buffer_;
    //std::pair<std::vector<Network::PlayerObject>, std::vector<Network::EnemyObject>> gameObject;
    boost::asio::streambuf buf;
    std::vector<std::thread> threadPool;
    std::map<std::string, int> myMap;
};
