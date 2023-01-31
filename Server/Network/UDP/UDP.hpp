/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** UDP.hpp
*/

#pragma once

#include "../interfaces/INetwork.hpp"

#define SIZE 1024

namespace RType {

    class UDP : public RType::INetwork {

        public:

            UDP(){
                //printf("UDP server constructed\n");
                //this->_socket = this->_Socket.SetSocket();
                //printf("the socket is %d\n", this->_socket);
                //this->_serverAddress = this->_Bind.BindSocketAddress(this->_socket);
            };

            ~UDP(){
                //printf("UDP server destructed\n");
            };

            ///temp, threading
            //void Run() override {};

            ///temp, testing purpose
            /*
            void Receive(RType::RecvFrom Receive, int socket, char *buffer, const struct sockaddr_in* address) override {
                Receive.GetRecvFrom(socket, (char *)buffer, SIZE, MSG_WAITALL, address);
            };
            */

            ///rb
            /*
            void Receive() override {
                this->_Receive.GetRecvFrom(this->_socket, static_cast<char *>(this->_buffer), SIZE, MSG_WAITALL, this->_serverAddress);
            };
            */

            ///temp, testing purpose
            /*
            void Send(RType::SendTo Send, int socket, uint_8 req, const struct sockaddr_in *address) override {
                Send.Send(socket, &req, 1, MSG_CONFIRM, address);
            };
            */

            ///rb
            /*
            void Send() override {
                this->_Send.Send(this->_socket, (&this->_req), 1, MSG_CONFIRM, this->_clientAddress);
            };
            */

            ///to implement,waiting for serv to glue graphic and ECS
            //void Kill() override {};

        protected:

            //RType::Context Ctx;
            //RType::Socket _Socket;
            //RType::Bind _Bind;
            //RType::RecvFrom _Receive;
            //RType::SendTo _Send;
            //int _socket = 0;
            //const struct sockaddr_in* _serverAddress;
            //const struct sockaddr_in* _clientAddress;
            /*std::vector<int, const struct sockaddr_in*> _clientAddress;*/ ///to fulfill later
            /*char _buffer[SIZE];
            uint8_t _req = 30;*/ ///temp, testing purpose
    };
}