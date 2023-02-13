/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** PopulateObject.hpp
*/

#pragma once

#include "PlayerObject.hpp"

namespace Network {
    class Populate {
    public:
        static Network::PlayerObject PlayerObject(int playerNumber, float x, float y);
    };

}