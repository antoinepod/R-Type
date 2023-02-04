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
#include <string>
#include <sstream>


const int num_threads = 4;
const int port_num = 8080;

class Server
{
public:
    explicit Server(boost::asio::io_service& service);
    ~Server();
    void startReceive();
    void handleReceive(size_t bytes_recvd);
    void workerThread(boost::asio::io_service& service);
    std::vector<float> manageData(const std::string& playerIp, std::vector<float >recvd_vec);

private:
    boost::asio::ip::udp::socket _socket;
    boost::asio::ip::udp::endpoint _remoteEndpoint;
    std::array<char, 1024> _recvBuf{};

    std::vector<std::pair<int, std::string>> _players;
    std::vector<float> _positions;
};
