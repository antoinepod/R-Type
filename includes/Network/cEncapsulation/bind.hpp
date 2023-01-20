/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** bind.hpp
*/

#pragma once

#include "cHead.hpp"
#include "cError.hpp"
#include <iostream>


namespace RType {

    class Bind {

        public:

            Bind() {};

            ~Bind() {};

            void BindSocketAddress(int socketFileDescriptor, struct sockaddr_in socketAddress, bool test = false) {
                if (!test) {
                    int err = bind(socketFileDescriptor, (const struct sockaddr *)&socketAddress,sizeof(socketAddress));
                    //printf("%d\n", errno);
                    if (err == -1)
                        throw RType::BindingError("Can't Bind");
                }
            };
    };
}
