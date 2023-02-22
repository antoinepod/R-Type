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

    void UpdateGame();
    int FindPlayer(int id);

    // Create objects
    void CreatePlayer(const std::string& ip, int id, const std::string& name);
    void CreateBullet(Network::Object & sender, float x, float y);

private:
    std::vector<Network::Object> _gameObject;
    std::shared_ptr<boost::asio::deadline_timer> _timer;
    int p_Id = 0;
    boost::asio::ip::udp::socket _socket;
    boost::asio::ip::udp::endpoint _remoteEndpoint;
    boost::array<unsigned char, 1> _recvBuffer;
    boost::asio::streambuf _buf;
    std::vector<std::thread> _threadPool;
    std::map<std::string, int> _myMap;
};
