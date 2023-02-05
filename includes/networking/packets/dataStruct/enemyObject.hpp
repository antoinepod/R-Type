/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** enemyObject.hpp
*/

#pragma once

#include "gameObject.hpp"

namespace RType {
    namespace Network {
        class EnemyObject : public GameObject {
            protected:
                double _x;
                double _y;
                double _v;
                int _health;
                int _strength;
                int _playerNumber;
                int _type;
        };
    }
}