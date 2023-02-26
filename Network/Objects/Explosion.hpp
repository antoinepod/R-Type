/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Explosion.hpp
*/

#pragma once

#include "Object.hpp"


namespace Network {
    class Explosion : public Object {
    public:
        Explosion();
        ~Explosion() override;
    };
}