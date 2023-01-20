/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** ServerUDP.hpp
*/

#pragma once

#include "UDP.hpp"

namespace RType {

    class ServerUDP : public RType::INetwork {

    public:

        ServerUDP(){
            printf("ServerUDP class constructed\n");
            this->_socket = this->_Socket.SetSocket();
            this->_initAddressStruct.initServerSocketAddress(&this->_serverAddress);
            this->_initAddressStruct.initClientAddress(&this->_clientAddress);
            char *ipServ = inet_ntoa(this->_serverAddress.sin_addr);
            printf("Server IP address is %s\n", ipServ);
            this->_Bind.BindSocketAddress(this->_socket, this->_serverAddress);
        };

        ~ServerUDP(){
            printf("ServerUDP class destroyed\n");
        };

        void Run() override {};

        void Send() override {
            std::cout << "Waiting to Send..." << std::endl;
            this->_Send.Send(this->_socket, (&this->_req), 1, MSG_CONFIRM, &this->_clientAddress);
            char *ipCli = inet_ntoa(this->_clientAddress.sin_addr);
            printf("Client IP address is %s\n", ipCli);
            std::cout << "Send done!" << std::endl;
        };

        void Receive() override {
            std::cout << "Waiting to Receive..." << std::endl;
            this->_Receive.GetRecvFrom(this->_socket, static_cast<char *>(this->_buffer), SIZE, MSG_WAITALL, &this->_clientAddress);
            std::cout << "Receive done!" << std::endl;
        };

        void Kill() override { close(this->_socket); };

    protected:

        RType::Context Ctx;
        RType::Socket _Socket;
        RType::Bind _Bind;
        RType::RecvFrom _Receive;
        RType::SendTo _Send;
        RType::SocketAddressStruct _initAddressStruct;
        int _socket = 0;
        struct sockaddr_in _serverAddress;
        struct sockaddr_in _clientAddress;
        /*std::vector<int, const struct sockaddr_in*> _clientAddress;*/ ///to fulfill later
        char _buffer[SIZE]; ///temp, testing purpose
        uint8_t _req = 30; ///temp, testing purpose
    };
}