/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** TCPServer.hpp
*/

#include <iostream>
#include <string>
#include <map>
#include <boost/asio.hpp>
#include "TCPSession.hpp"

using boost::asio::ip::tcp;

class Server {
public:
    Server(boost::asio::io_service& io_service, short port);
    ~Server();

    std::map<std::string, int> getClients() const;

private:
    void Accept();

    tcp::acceptor _acceptor;
    std::map<std::string, int> _clients;
};