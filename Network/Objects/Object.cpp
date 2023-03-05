/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Object.cpp
*/

#include "Object.hpp"


namespace Network {
    Object::Object() {
        _x = 0;
        _y = 0;
        _v = 0;
        _health = 0;
        _strength = 0;
        _type = ObjectType::UNDEFINED;
        _id = 0;
        _destroyable = false;
        _name = "";
        _frame = 0;
        _explosion = (ExplosionType)0;
        _bullet = (BulletType)0;
        _sound = (SoundType)0;
        _gameState = (GameState)0;
        _fullHealth = 0;
    };

    Object::~Object() = default;

    // Setters
    void Object::setGameState(GameState gameState) {
        _gameState = gameState;
    }
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
    void Object::setExplosion(ExplosionType explosion) {
        _explosion = explosion;
    }
    void Object::setBullet(BulletType bullet) {
        _bullet = bullet;
    }
    void Object::setSound(SoundType sound) {
        _sound = sound;
    }
    void Object::setEnemy(EnemyType enemyType) {
        _enemyType = enemyType;
    }
    void Object::setFullHealth(int fullHealth) {
        _fullHealth = fullHealth;
    }

    // Getters
    GameState Object::getGameState() {
        return _gameState;
    }
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
    ExplosionType Object::getExplosion() {
        return _explosion;
    }
    BulletType Object::getBullet() {
        return _bullet;
    }
    SoundType Object::getSound() {
        return _sound;
    }
    EnemyType Object::getEnemy() {
        return _enemyType;
    }
    int Object::getFullHealth() {
        return _fullHealth;
    }
}
