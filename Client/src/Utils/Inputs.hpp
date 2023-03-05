/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-william.mallevays
** File description:
** Inputs.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "Data/Enums.hpp"


class Inputs {
public:
    Inputs();
    ~Inputs();


    // Getters
    Action GetAction();
    Action GetShoot();

    // Setters
    void SetKey(Action, sf::Keyboard::Key key);

private:
    std::map<Action, sf::Keyboard::Key> _keys;
};