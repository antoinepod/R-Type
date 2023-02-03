/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-william.mallevays
** File description:
** Server.hpp
*/

#include <iostream>
#include <vector>
#include <thread>
#include <boost/asio.hpp>


const int num_threads = 4;
const int port_num = 8080;

class Server
{
public:
    explicit Server(boost::asio::io_service& service);
    ~Server();
    void start_receive();
    void handle_receive(size_t bytes_recvd);
    void worker_thread(boost::asio::io_service& service);

private:
    boost::asio::ip::udp::socket socket;
    boost::asio::ip::udp::endpoint remote_endpoint;
    std::array<char, 1024> recv_buf{};
};
