/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** UDPServer.cpp
*/

#pragma once

#include "../packets/serialization/serialization.hpp"
#include "../packets/deserialization/deserialization.hpp"

using boost::asio::ip::udp;

class udp_server
{
public:
    udp_server(boost::asio::io_context& io_context)
            : socket_(io_context, udp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 8080))
    {
        start_receive();
        //if (!recv_buffer_.empty) {
            //std::cout << "Client message :" << recv_buffer_.c_array() << std::endl;
            //std::cout << "Address :" << remote_endpoint_.address() << std::endl;
        //}
    }

private:
    void start_receive()
    {
        socket_.async_receive_from(boost::asio::buffer(recv_buffer_), remote_endpoint_,boost::bind(&udp_server::handle_receive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
        std::cout << "" << std::to_string(recv_buffer_.data()[0]) << std::endl;
    }

    void handle_receive(const boost::system::error_code& error,std::size_t)
    {
        if (!error)
        {
            seria.S_erialize(gameObject, &buf);
            std::string strBuf(boost::asio::buffers_begin(buf.data()),boost::asio::buffers_end(buf.data()));
            boost::shared_ptr<std::string> message(new std::string(strBuf));
            //std::cout << "" << *message << std::endl;
            //std::cout << "Serialized data size: " << buf.size() << "and mess length: " << message->length() << std::endl;
            socket_.async_send_to(boost::asio::buffer(*message), remote_endpoint_, boost::bind(&udp_server::handle_send, this, message, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
            buf.consume(buf.size());
            start_receive();
        }
    }

    void handle_send(boost::shared_ptr<std::string>,const boost::system::error_code&,std::size_t){}

    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    boost::array<char, 1> recv_buffer_;
    RType::Network::Seria seria;
    std::pair<std::vector<RType::Network::PlayerObject>, std::vector<RType::Network::EnemyObject>> gameObject = RType::Network::populateObject();
    boost::asio::streambuf buf;
};
