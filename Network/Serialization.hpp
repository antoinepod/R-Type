/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** serialization.hpp
*/

#pragma once

#include "Data/PopulateObject.hpp"

    namespace Network {
        template <typename T>
        void serialize(boost::asio::streambuf& buf, const T& t) {
            std::ostream os(&buf);
            //std::cout << "size is: " << sizeof(t) << std::endl;
            os.write(reinterpret_cast<const char*>(&t), sizeof(t));
        }

        class Seria {
        public:
            static void S_erialize(std::vector<Network::Object> gameObject, boost::asio::streambuf *buf);
        };
    }