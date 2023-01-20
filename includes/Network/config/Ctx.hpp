/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** ctx.hpp
*/

#pragma once

#include <string>
#include <vector>
#include "../cEncapsulation/cHead.hpp"

namespace RType {

    class Context {

        public:

            Context() {};

            ~Context() {};

            void SetSocketFileDescriptor(int socket) {
                this->_socket = socket;
            };

            [[maybe_unused]] void SetServerAddress(const struct sockaddr_in* address) {
                this->_serverSocketAddress = address;
            };

            [[maybe_unused]] void SetClientAddress(const struct sockaddr_in* address) {
                this->_clientSocketAddress = address;
            };

            //[[maybe_unused]] void SetClientAddressArray(std::vector<int, const struct sockaddr_in*> addressArray) {
            //    this->_clientAddressArray = addressArray;
            //};

            int GetSocketFileDescriptor() {
                return this->_socket;
            };

            [[maybe_unused]] const struct sockaddr_in* GetServerAddress() {
                return this->_serverSocketAddress;
            };

            [[maybe_unused]] const struct sockaddr_in* GetClientAddress() {
                return this->_clientSocketAddress;
            };

            //[[maybe_unused]] std::vector<int, const struct sockaddr_in*> GetClientAddressArray() {
            //    return this->_clientAddressArray;
            //};

        protected:
            int _socket = 0;
            const struct sockaddr_in* _serverSocketAddress;
            const struct sockaddr_in* _clientSocketAddress;
            //std::vector<int, const struct sockaddr_in*> _clientAddressArray;
    };
}