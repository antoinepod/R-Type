/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** populateObject.hpp
*/

#pragma once

#include "playerObject.hpp"
#include "enemyObject.hpp"

namespace Network {
    class Populate {
    public:
        Populate();
        ~Populate();

        static Network::PlayerObject PlayerObject(int playerNumber, float x, float y);
    };

}