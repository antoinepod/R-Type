/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** IGameObject.hpp
*/

#pragma once

#include "../includes/enums.hpp"

namespace RType {
    namespace Network {
        class IGameObject {
            public:
                ~IGameObject() = default;
                virtual void setX(float x) = 0;
                virtual void setY(float y) = 0;
                virtual void setCelerity(float v) = 0;
                virtual void setHealth(int health) = 0;
                virtual void setStrength(int strength) = 0;
                virtual void setType(int type) = 0;
                virtual float getX() = 0;
                virtual float getY() = 0;
                virtual float getCelerity() = 0;
                virtual int getHealth() = 0;
                virtual int getStrength() = 0;
                virtual int getType() = 0;
        };
    }
}