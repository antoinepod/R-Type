/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** socket.hpp
*/

#pragma once

#include "cHead.hpp"
#include "cError.hpp"

namespace RType {

    class Socket {

        public:

            Socket() {};

            ~Socket(){};

            int SetSocket() {
                printf("Set socket...\n");
                this->_socketFileDescriptor = socket(this->_domain, this->_type, this->_protocol);
                if (this->_socketFileDescriptor == -1)
                    throw RType::BindingError("Socket creation failure");
                printf("Socket fd: %d\n", this->_socketFileDescriptor);
                return this->GetSocketFileDescriptor();
            };

            int GetSocketFileDescriptor() {
                return this->_socketFileDescriptor;
            };

        protected:

            int _socketFileDescriptor = -1;
            int _domain = AF_INET;
            int _type = SOCK_DGRAM;
            int _protocol = 0;
    };
}
