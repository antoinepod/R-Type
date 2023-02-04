//
// Created by pan on 31/01/23.
//

#pragma once

#include <ctime>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include "../packets/serialization/serialization.hpp"

using boost::asio::ip::udp;

std::string make_daytime_string()
{
    using namespace std; // For time_t, time and ctime;
    time_t now = time(0);
    return ctime(&now);
}

class udp_server
{
public:
    udp_server(boost::asio::io_context& io_context)
            : socket_(io_context, udp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 8080))
    {
        start_receive();
        std::cout << "Client message :" << recv_buffer_.c_array() << std::endl;
        std::cout << "Address :" << remote_endpoint_.address() << std::endl;
    }

private:
    void start_receive()
    {
        socket_.async_receive_from(boost::asio::buffer(recv_buffer_), remote_endpoint_,boost::bind(&udp_server::handle_receive, this,boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred));
    }

    void handle_receive(const boost::system::error_code& error,std::size_t)
    {
        if (!error)
        {
            //boost::shared_ptr<std::string> message(
            //        new std::string(make_daytime_string()));
            //boost::shared_ptr<boost::asio::streambuf> buf = boost::make_shared<seria.S_erialize()>;
            //std::shared_ptr<boost::asio::streambuf> buf = std::make_shared<seria.S_erialize(gameObject)>;
//
            //socket_.async_send_to(boost::asio::buffer(), remote_endpoint_,
            //                      boost::bind(&udp_server::handle_send, this, message,
            //                                  boost::asio::placeholders::error,
            //                                  boost::asio::placeholders::bytes_transferred));

            start_receive();
        }
    }

    void handle_send(boost::shared_ptr<std::string>,const boost::system::error_code&,std::size_t){}

    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    boost::array<char, 1> recv_buffer_;
    RType::Network::Seria seria;
    std::pair<std::vector<RType::Network::PlayerObject>, std::vector<RType::Network::EnemyObject>> gameObject = RType::Network::populateObject();

};
