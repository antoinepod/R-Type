/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** enemyObject.hpp
*/

#pragma once

#include "gameObject.hpp"

    namespace Network {
        class EnemyObject : public GameObject {
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