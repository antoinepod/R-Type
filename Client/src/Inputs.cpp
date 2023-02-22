/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-william.mallevays
** File description:
** Inputs.cpp
*/

#include "Inputs.hpp"

Inputs::Inputs() {
    _up = sf::Keyboard::Up;
    _down = sf::Keyboard::Down;
    _left = sf::Keyboard::Left;
    _right = sf::Keyboard::Right;
    _ok = sf::Keyboard::Enter;
}

Inputs::~Inputs() = default;

bool Inputs::GetUp() const {
    return sf::Keyboard::isKeyPressed(_up) ;
}

bool Inputs::GetDown() const {
    return sf::Keyboard::isKeyPressed(_down);
}

bool Inputs::GetLeft() const {
    return sf::Keyboard::isKeyPressed(_left);
}

bool Inputs::GetRight() const {
    return sf::Keyboard::isKeyPressed(_right);
}

bool Inputs::GetOK() const {
    return sf::Keyboard::isKeyPressed(_ok);
}

void Inputs::SetUp(sf::Keyboard::Key key) {
    _up = key;
}

void Inputs::SetDown(sf::Keyboard::Key key) {
    _down = key;
}

void Inputs::SetLeft(sf::Keyboard::Key key) {
    _left = key;
}

void Inputs::SetRight(sf::Keyboard::Key key) {
    _right = key;
}

void Inputs::SetOK(sf::Keyboard::Key key) {
    _ok = key;
}
