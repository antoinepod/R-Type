/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Player.hpp
*/

#pragma once

#include "Object.hpp"


namespace Network {
    class Player : public Object {
    public:
        Player();
        ~Player() override;
    };
}