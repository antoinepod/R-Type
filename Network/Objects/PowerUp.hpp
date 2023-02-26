/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** PowerUp.hpp
*/

#pragma once

#include "Object.hpp"


namespace Network {
    class PowerUp : public Object {
    public:
        PowerUp();
        ~PowerUp() override;
    };
}