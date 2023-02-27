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
        void setType(ObjectType type) override;
        void setId(int id) override;
        void setDestroyable(bool destroyable) override;
        void setName(const std::string &name) override;
        void setFrame(int frame) override;
        void setExplosion(ExplosionType explosion) override;
        void setBullet(BulletType bullet) override;
        void setSound(SoundType sound) override;

        // Getters
        float getX() override;
        float getY() override;
        float getCelerity() override;
        int getHealth() override;
        int getStrength() override;
        ObjectType getType() override;
        int getId() override;
        bool getDestroyable() override;
        std::string getName() override;
        int getFrame() override;
        ExplosionType getExplosion() override;
        BulletType getBullet() override;
        SoundType getSound() override;

    private:
        float _x;
        float _y;
        float _v;
        int _health;
        int _strength;
        ObjectType _type;
        int _id;
        bool _destroyable;
        std::string _name;
        int _frame;
        ExplosionType _explosion;
        BulletType _bullet;
        SoundType _sound;
    };
}