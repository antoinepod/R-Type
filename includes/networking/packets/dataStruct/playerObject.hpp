/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** playerObject.hpp
*/

#pragma once

#include "gameObject.hpp"

namespace RType {
    namespace Network {
        class PlayerObject : public GameObject {
            protected:
                float _x;
                float _y;
                float _v;
                int _health;
                int _strength;
                int _playerNumber;
                int _type;
        };
    }
}