/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** TCPServer.cpp
*/

#include "TCPServer.hpp"

Server::Server(boost::asio::io_service& io_service, short port) : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)), _clients() {
    Accept();
}

Server::~Server() = default;

void Server::Accept() {
    acceptor_.async_accept([this](boost::system::error_code ec, tcp::socket socket) {
        if (!ec) {
            std::make_shared<Session>(std::move(socket), _clients)->Start();
        }
        Accept();
    });
}
