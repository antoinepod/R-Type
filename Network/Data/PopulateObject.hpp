/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** PopulateObject.hpp
*/

#pragma once

#include "Objects/Player.hpp"

namespace Network {
    class Populate {
    public:
        static Network::Player Player(int playerNumber, float x, float y);
    };

}