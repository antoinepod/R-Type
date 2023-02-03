/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-william.mallevays
** File description:
** Server.cpp
*/

#include "Server.hpp"


Server::Server(boost::asio::io_service& service) : socket(service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port_num))
{
    start_receive();
}

Server::~Server()
{
}

void Server::start_receive()
{
    socket.async_receive_from(boost::asio::buffer(recv_buf), remote_endpoint, [this](const boost::system::error_code& ec, size_t bytes_recvd) {
        if (!ec && bytes_recvd > 0) {
            handle_receive(bytes_recvd);
        } else {
            std::cout << "Error: " << ec.message() << std::endl;
        }
        start_receive();
    });
}

void Server::handle_receive(size_t bytes_recvd)
{
    std::cout << "Received message from " << remote_endpoint << ": ";
    std::vector<int> recvd_vec(bytes_recvd / sizeof(int));
    memcpy(recvd_vec.data(), recv_buf.data(), bytes_recvd);
    for (int num : recvd_vec)  {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    socket.async_send_to(boost::asio::buffer("Hello from the server"), remote_endpoint, [this](const boost::system::error_code& ec, size_t bytes_sent) {
        if (!ec) {
            std::cout << "Sent message to " << remote_endpoint << std::endl;
        } else {
            std::cout << "Error: " << ec.message() << std::endl;
        }
    });
}

void Server::worker_thread(boost::asio::io_service& service)
{
    service.run();
}

