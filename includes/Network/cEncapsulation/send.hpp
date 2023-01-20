/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** send.hpp
*/

#pragma once

#include "cHead.hpp"

namespace RType {

    class SendTo {

        public:

            SendTo(){};

            ~SendTo(){};

            void Send(int socketFileDescriptor, const void *buffer, size_t length, int flags, struct sockaddr_in *destinationAddress) {
                //socklen_t addressLength = sizeof(destinationAddress);
                int err = sendto(socketFileDescriptor, buffer, length, flags, (sockaddr*)destinationAddress, sizeof(*destinationAddress));
                if (err < 0)
                    printf("%d", errno);
            };
    };
}
