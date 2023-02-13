/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** deserialization.hpp
*/

#pragma once

#include "Data/PlayerObject.hpp"

    namespace Network {
        class Deseria {
        public:
            static std::vector<Network::GameObject> D_eserialize(boost::array<char, 1024>& buffer);
            static std::size_t getMeta(boost::array<char, 1024> buffer, std::size_t& pos);
            static int getIntValue(boost::array<char, 1024> buffer, std::size_t& pos);
            static float getFloatValue(boost::array<char, 1024> buffer, std::size_t& pos);
        };
    }
