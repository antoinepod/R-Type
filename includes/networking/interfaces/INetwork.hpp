/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** INetwork.hpp
*/

#pragma once

#include "../includes/enums.hpp"

namespace RType {
    namespace Network {
        class INetwork {
            virtual ~INetwork() = default;
            virtual void Run() = 0;
            virtual int SocketFd() = 0;
            virtual int BindAddress() = 0;
            //virtual int Send() = 0;
            //virtual int Receive() = 0;
            virtual void Kill() = 0;
        };
    }
}