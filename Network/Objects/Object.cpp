/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Object.cpp
*/

#include "Object.hpp"


namespace Network {
    Object::Object() = default;

    Object::~Object() = default;

    // Setters
    void Object::setX(float x) {
        _x = x;
    }
    void Object::setY(float y) {
        _y = y;
    }
    void Object::setCelerity(float v) {
        _v = v;
    }
    void Object::setHealth(int health) {
        _health = health;
    }
    void Object::setStrength(int strength) {
        _strength = strength;
    }
    void Object::setType(RType::ObjectType type) {
        _type = type;
    }
    void Object::setId(int id) {
        _id = id;
    }

    // Getters
    float Object::getX() {
        return _x;
    }
    float Object::getY() {
        return _y;
    }
    float Object::getCelerity() {
        return _v;
    }
    int Object::getHealth() {
        return _health;
    }
    int Object::getStrength() {
        return _strength;
    }
    RType::ObjectType Object::getType() {
        return _type;
    }
    int Object::getId() {
        return _id;
    }
}
