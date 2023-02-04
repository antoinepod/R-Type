#include "gameObject.hpp"

void RType::Network::GameObject::setX(double x) {
    this->_x = x;
}

void RType::Network::GameObject::setY(double y) {
    this->_y = y;
}

void RType::Network::GameObject::setCelerity(double v) {
    this->_v = v;
}

void RType::Network::GameObject::setHealth(int health) {
    this->_health = health;
}

void RType::Network::GameObject::setStrength(int strength) {
    this->_strength = strength;
}

void RType::Network::GameObject::setType(int type) {
    this->_type = type;
}

void RType::Network::GameObject::setPlayerNumber(int playerNumber) {
    this->_playerNumber = playerNumber;
}

double RType::Network::GameObject::getX() {
    return this->_x;
}

double RType::Network::GameObject::getY() {
    return this->_y;
}

double RType::Network::GameObject::getCelerity() {
    return this->_v;
}

int RType::Network::GameObject::getHealth() {
    return this->_health;
}

int RType::Network::GameObject::getStrength() {
    return this->_strength;
}

int RType::Network::GameObject::getType() {
    return this->_type;
}

int RType::Network::GameObject::getPlayerNumber() {
    return this->_playerNumber;
}