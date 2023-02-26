/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** deserialization.hpp
*/

#pragma once

#include "Objects/Player.hpp"
#include "Objects/Bullet.hpp"
#include "Objects/Enemy.hpp"
#include "Objects/PowerUp.hpp"
#include "Objects/Explosion.hpp"

namespace Network {
    class Deseria {
    public:
        static std::vector<Network::Object> D_eserialize(boost::array<char, 1024>& buffer);
        static std::size_t getMeta(boost::array<char, 1024> buffer, std::size_t& pos);
        static int getIntValue(boost::array<char, 1024> buffer, std::size_t& pos);
        static float getFloatValue(boost::array<char, 1024> buffer, std::size_t& pos);
        static std::string getStringValue(boost::array<char, 1024> buffer, std::size_t& pos);
    };
}
