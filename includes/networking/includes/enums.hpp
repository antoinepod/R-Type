/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** enums.hpp
*/

#pragma once

#include "headers.hpp"

namespace RType {

    enum Actions {
        UP = 2,
        RIGHT = 4,
        DOWN = 8,
        LEFT = 16,
        EVENT = 32
    };

    enum Events {
        SHOT = 64,
    };
}
