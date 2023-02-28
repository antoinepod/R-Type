/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-william.mallevays
** File description:
** Inputs.cpp
*/

#include "Inputs.hpp"

Inputs::Inputs() {
    _keys[Action::SIMPLE_SHOOT] = sf::Keyboard::Space;
    _keys[Action::LASER_SHOOT] = sf::Keyboard::X;
    _keys[Action::ROCKET_SHOOT] = sf::Keyboard::C;
    _keys[Action::UP] = sf::Keyboard::Up;
    _keys[Action::DOWN] = sf::Keyboard::Down;
    _keys[Action::LEFT] = sf::Keyboard::Left;
    _keys[Action::RIGHT] = sf::Keyboard::Right,
    _keys[Action::LEVEL1] = sf::Keyboard::Num1;
    _keys[Action::LEVEL2] = sf::Keyboard::Num2;
    _keys[Action::LEVEL3] = sf::Keyboard::Num3;
    _keys[Action::LEVEL4] = sf::Keyboard::Num4;
    _keys[Action::LEVEL5] = sf::Keyboard::Num5;
}

Inputs::~Inputs() = default;

Action Inputs::GetAction() {
    for (auto &key : _keys) {
        if (sf::Keyboard::isKeyPressed(key.second) && key.first != Action::SIMPLE_SHOOT
        && key.first != Action::LASER_SHOOT && key.first != Action::ROCKET_SHOOT)
            return key.first;
    }
    return Action::NONE;
}

void Inputs::SetKey(Action action, sf::Keyboard::Key key) {
    _keys[action] = key;
}

Action Inputs::GetShoot() {
    if (sf::Keyboard::isKeyPressed(_keys[SIMPLE_SHOOT]))
        return Action::SIMPLE_SHOOT;
    else if (sf::Keyboard::isKeyPressed(_keys[LASER_SHOOT]))
        return Action::LASER_SHOOT;
    else if (sf::Keyboard::isKeyPressed(_keys[ROCKET_SHOOT]))
        return Action::ROCKET_SHOOT;
    else
        return Action::NONE;

}
