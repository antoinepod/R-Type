/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** PlayerObject.hpp
*/

#pragma once

#include "GameObject.hpp"

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