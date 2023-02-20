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
#include "UDPServer.hpp"

using boost::asio::ip::tcp;

class TCPServer {
public:
    TCPServer(boost::asio::io_service& io_service, short port, UDPServer& udpServer);
    ~TCPServer();

    std::map<std::string, int> getClients() const;

private:
    void Accept(UDPServer& udpServer);

    tcp::acceptor _acceptor;
    std::map<std::string, int> _clients;
};