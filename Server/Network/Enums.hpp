/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Enums.hpp
*/

#pragma once

namespace RType {

    /// to uint_8 or uint_16 ?
    enum Actions {
        UP = 2,
        RIGHT = 4,
        DOWN = 8,
        LEFT = 16,
        EVENT = 32
    };

    /// to uint_16 ?
    enum Events {
        SHOT = 64,
        DIE = 128,
        QUIT = 256
    };
}
