/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** initSocketAddressStruct.hpp
*/

#pragma once

#include "cHead.hpp"

namespace RType {

    class SocketAddressStruct {

    public:

        SocketAddressStruct() {};

        ~SocketAddressStruct() {};

        struct sockaddr_in *initServerSocketAddress(struct sockaddr_in *socketAddress) {
            memset(socketAddress, 0, sizeof(*socketAddress));
            socketAddress->sin_family = AF_INET;
            //socketAddress->sin_addr.s_addr = inet_addr("127.0.0.1");
            socketAddress->sin_addr.s_addr = INADDR_ANY;
            socketAddress->sin_port = htons(8080);
            return socketAddress;
        };

        struct sockaddr_in *initClientAddress(struct sockaddr_in *socketAddress) {
            memset(socketAddress, 0, sizeof(*socketAddress));
            return socketAddress;
        }
    };
}
