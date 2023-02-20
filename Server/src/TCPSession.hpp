/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** TCPSession.hpp
*/

#include <map>
#include <iostream>
#include <boost/asio.hpp>
#include "UDPServer.hpp"

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
public:
    Session(tcp::socket socket, std::map<std::string, int>& clients);
    ~Session();

    void Start(UDPServer& udpServer);

private:
    void Write(const std::string& client_id);
    void Read();
    void HandleRead(std::size_t length);
    static std::string GenerateId();

    tcp::socket _socket;
    std::map<std::string, int>& _clients;
    std::string _clientId;
    enum { max_length = 1024 };
    char _data[max_length]{};
};