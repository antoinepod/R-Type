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
    void Object::setType(ObjectType type) {
        _type = type;
    }
    void Object::setId(int id) {
        _id = id;
    }
    void Object::setDestroyable(bool destroyable) {
        _destroyable = destroyable;
    }
    void Object::setName(const std::string &name) {
        _name = name;
    }
    void Object::setFrame(int frame) {
        _frame = frame;
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
    ObjectType Object::getType() {
        return _type;
    }
    int Object::getId() {
        return _id;
    }
    bool Object::getDestroyable() {
        return _destroyable;
    }
    std::string Object::getName() {
        return _name;
    }
    int Object::getFrame() {
        return _frame;
    }
}
