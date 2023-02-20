/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** IObject.hpp
*/

#pragma once

#include "Data/Enums.hpp"

namespace Network {
    class IObject {
    public:
        virtual ~IObject() = default;

        // Setters
        virtual void setX(float x) = 0;
        virtual void setY(float y) = 0;
        virtual void setCelerity(float v) = 0;
        virtual void setHealth(int health) = 0;
        virtual void setStrength(int strength) = 0;
        virtual void setType(ObjectType type) = 0;
        virtual void setId(int id) = 0;
        virtual void setDestroyable(bool destroyable) = 0;

        // Getters
        virtual float getX() = 0;
        virtual float getY() = 0;
        virtual float getCelerity() = 0;
        virtual int getHealth() = 0;
        virtual int getStrength() = 0;
        virtual ObjectType getType() = 0;
        virtual int getId() = 0;
        virtual bool getDestroyable() = 0;
    };
}
