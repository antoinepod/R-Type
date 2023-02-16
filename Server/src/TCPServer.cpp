/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** TCPServer.cpp
*/

#include "TCPServer.hpp"

Server::Server(boost::asio::io_service& io_service, short port) : _acceptor(io_service, tcp::endpoint(tcp::v4(), port)), _clients() {
    this->Accept();
}

Server::~Server() = default;

void Server::Accept() {
    _acceptor.async_accept([this](boost::system::error_code ec, tcp::socket socket) {
        if (!ec) {
            std::make_shared<Session>(std::move(socket), _clients)->Start();
        }
        Accept();
    });
}

std::map<std::string, int> Server::getClients() const {
    return _clients;
}
