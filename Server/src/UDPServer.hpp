/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** UDPServer.hpp
*/

#pragma once

#include "Serialization.hpp"
#include "Deserialization.hpp"

class UDPServer
{
public:
    explicit UDPServer(boost::asio::io_context& io_context);
    ~UDPServer();

    void StartReceive();
    void Receive(const boost::system::error_code& error,std::size_t);
    void Send(boost::shared_ptr<std::string>,const boost::system::error_code&,std::size_t);

private:
    std::vector<Network::Object> gameObject;
    int p_Id = 0;
    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint remote_endpoint_;
    boost::array<unsigned char, 1> recv_buffer_;
    boost::asio::streambuf buf;
    std::vector<std::thread> threadPool;
    std::map<std::string, int> myMap;
};
