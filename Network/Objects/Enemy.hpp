/*
** EPITECH PROJECT, 2023
** r-type_client
** File description:
** Enemy.hpp
*/

#pragma once

#include "Object.hpp"

namespace Network {
    class Enemy : public Object {
    public:
        Enemy();
        ~Enemy() override;
    };
}