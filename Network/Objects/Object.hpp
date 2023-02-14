/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Object.hpp
*/

#pragma once

#include "IObject.hpp"

namespace Network {
    class Object : public IObject {
    public:
        Object();
        ~Object() override;

        // Setters
        void setX(float x) override;
        void setY(float y) override;
        void setCelerity(float v) override;
        void setHealth(int health) override;
        void setStrength(int strength) override;
        void setType(RType::ObjectType type) override;
        void setId(int id) override;
        void setDestroyable(bool destroyable) override;

        // Getters
        float getX() override;
        float getY() override;
        float getCelerity() override;
        int getHealth() override;
        int getStrength() override;
        RType::ObjectType getType() override;
        int getId() override;
        bool getDestroyable() override;

    private:
        float _x;
        float _y;
        float _v;
        int _health;
        int _strength;
        RType::ObjectType _type;
        int _id;
        bool _destroyable;
    };
}