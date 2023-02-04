/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-william.mallevays
** File description:
** Server.cpp
*/

#include "Server.hpp"


Server::Server(boost::asio::io_service& service) : _socket(service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port_num))
{
    startReceive();
    _players = {};
    _positions = {};
}

Server::~Server()
{
}

void Server::startReceive()
{
    _socket.async_receive_from(boost::asio::buffer(_recvBuf), _remoteEndpoint, [this](const boost::system::error_code& ec, size_t bytes_recvd) {
        if (!ec && bytes_recvd > 0) {
            handleReceive(bytes_recvd);
        } else {
            std::cout << "Error: " << ec.message() << std::endl;
        }
        startReceive();
    });
}

void Server::handleReceive(size_t bytes_recvd)
{
    std::cout << "Received message from " << _remoteEndpoint << ": ";
    std::vector<float> recvd_vec(bytes_recvd / sizeof(float));
    memcpy(recvd_vec.data(), _recvBuf.data(), bytes_recvd);
    for (float num : recvd_vec)  {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::stringstream tmp;
    tmp << _remoteEndpoint;

    _positions = manageData(tmp.str(), recvd_vec);

    _socket.async_send_to(boost::asio::buffer("Hello from the server"), _remoteEndpoint, [this](const boost::system::error_code& ec, size_t bytes_sent) {
        if (!ec) {
            std::cout << "Sent message to " << _remoteEndpoint << std::endl;
        } else {
            std::cout << "Error: " << ec.message() << std::endl;
        }
    });
}

void Server::workerThread(boost::asio::io_service& service)
{
    service.run();
}

std::vector<float> Server::manageData(const std::string& playerIp, std::vector<float> recvd_vec) {
    int player_id = -1;

    for (auto& p : _players) {
        if (p.second == playerIp) {
            player_id = p.first;
            break;
        }
    }

    if (_players.empty())
        player_id = 1;
    else
        player_id = _players.back().first + 1;

    if (player_id == -1) {
        std::pair<int, std::string> new_player = std::make_pair(player_id, playerIp);
        _players.push_back(new_player);
        player_id = _players.back().first;
    }

    bool playerExists = false;
    for (int i = 0; i < _positions.size(); i += 3) {
        if (_positions[i] == (float)player_id) {
            _positions[1] = recvd_vec[0];
            _positions[2] = recvd_vec[1];
            playerExists = true;
        }
    }
    if (!playerExists) {
        _positions.push_back((float)player_id);
        _positions.push_back(recvd_vec[0]);
        _positions.push_back(recvd_vec[1]);
    }

    for (auto& num : _positions)
        std::cout << num << " ";

    return _positions;
}

