/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Bullet.hpp
*/

#pragma once

#include "Object.hpp"


namespace Network {
    class Bullet : public Object {
    public:
        Bullet();
        ~Bullet() override;
    };
}