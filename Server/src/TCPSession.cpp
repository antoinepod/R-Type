/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** TCPSession.cpp
*/

#include "TCPSession.hpp"

Session::Session(tcp::socket socket, std::map<std::string, int>& clients) : _socket(std::move(socket)), _clients(clients) {};

Session::~Session() = default;

void Session::Start() {
//    std::string client_id = GenerateId();
//    _clients[client_id] = 0;
//
//    std::cout << "Client connected with ID: " << client_id << std::endl;
//
//    Write(client_id);

    std::string client_id;

    // Check if this client has a stored ID
    std::string client_address = _socket.remote_endpoint().address().to_string();
    if (_clients.count(client_address) == 0) {
        // Generate a new ID for this client
        client_id = GenerateId();
        _clients[client_address] = std::stoi(client_id);
    }
    else {
        // Use the stored ID for this client
        client_id = std::to_string(_clients[client_address]);
    }

    std::cout << "Client " << client_address << " connected with ID: " << client_id << std::endl;

    Write(client_id);
}


void Session::Write(const std::string& client_id) {
    std::string message = "Your ID is: " + client_id;
    boost::asio::async_write(_socket, boost::asio::buffer(message), [shared_this = shared_from_this()](boost::system::error_code ec, std::size_t) {
        if (!ec) {
            shared_this->Read();
        }
    });
}

void Session::Read() {
    boost::asio::async_read(_socket, boost::asio::buffer(_data, max_length), [shared_this = shared_from_this()](boost::system::error_code ec, std::size_t length) {
        if (!ec) {
            shared_this->HandleRead(length);
        }
    });
}

void Session::HandleRead(std::size_t length) {
    std::cout << "Received " << length << " bytes from client." << std::endl;

    _clients[_clientId] += (int)length;

    Write(_clientId);
}

std::string Session::GenerateId() {
    static int id_counter = 0;
    return std::to_string(++id_counter);
}
