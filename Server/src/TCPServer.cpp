/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** TCPServer.cpp
*/

#include "TCPServer.hpp"

TCPServer::TCPServer(boost::asio::io_service& io_service, short port, UDPServer& udpServer) : _acceptor(io_service, tcp::endpoint(tcp::v4(), port)), _clients() {
    this->Accept(udpServer);
}

TCPServer::~TCPServer() = default;

void TCPServer::Accept(UDPServer& udpServer) {
    _acceptor.async_accept([this, &udpServer](boost::system::error_code ec, tcp::socket socket) {
        if (!ec) {
            std::make_shared<Session>(std::move(socket), _clients)->Start(udpServer);
        }
        Accept(udpServer);
    });
}

std::map<std::string, int> TCPServer::getClients() const {
    return _clients;
}
