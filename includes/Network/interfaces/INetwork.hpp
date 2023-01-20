/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** INetwork.hpp
*/

#pragma once

#include <string>
#include "../cEncapsulation/bind.hpp"
#include "../cEncapsulation/recvfrom.hpp"
#include "../cEncapsulation/send.hpp"
#include "../cEncapsulation/socket.hpp"
#include "../config/Ctx.hpp"
#include "../cEncapsulation/initSocketAddressStruct.hpp"

namespace RType {

    class INetwork {

        public:

            virtual ~INetwork() = default;
            virtual void Run() = 0;
            virtual void Receive() = 0;
            virtual void Send() = 0;
            virtual void Kill() = 0;
            //virtual void SetSocket() = 0;
            //virtual int SetSocketOptions(int socketFileDescriptor, int level, int optionName,  const void *optionValue, socklen_t length) = 0;
            //virtual int BindSocketAddress(int socketFileDescriptor, const struct sockaddr *socketAddress) = 0;
            //virtual int Listen(int socketFileDescriptor, int backLog) = 0;
            //virtual int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) = 0;
            //virtual void GetRecvFrom(int socketFileDescriptor, void *buf, size_t length, int flags, struct sockaddr *address, socklen_t *addressLength) = 0;
            //virtual void Send(int sockFileDescriptor, const void *buf, size_t length, int flags, const struct sockaddr *destinationAddress, socklen_t addressLength) = 0;
    };
}