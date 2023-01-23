/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** recvfrom.hpp
*/

#pragma once

#include "cHead.hpp"

namespace RType {

    class RecvFrom {

        public:

            RecvFrom(){};

            ~RecvFrom(){};

            int GetRecvFrom(int socketFileDescriptor, void *buffer, size_t length, int flags, const struct sockaddr_in *sourceAddress) {
                socklen_t addressLength = sizeof(sourceAddress);
                int n = recvfrom(socketFileDescriptor, buffer, length, flags, (sockaddr*)sourceAddress, &addressLength);
                return n;
            };

            ///rb
            /*
            int GetRecvFrom(int socketFileDescriptor, char *buffer, size_t length, int flags, const struct sockaddr_in *sourceAddress) {
                socklen_t addressLength = sizeof(sourceAddress);
                int n = recvfrom(socketFileDescriptor, buffer, length, flags, (sockaddr*)sourceAddress, &addressLength);
                return n;
            };
            */
    };
}
