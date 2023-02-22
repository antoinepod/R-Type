/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-william.mallevays
** File description:
** Inputs.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>


class Inputs {
public:
    Inputs();
    ~Inputs();

    // Getters
    bool GetUp() const;
    bool GetDown() const;
    bool GetLeft() const;
    bool GetRight() const;
    bool GetOK() const;

    // Setters
    void SetUp(sf::Keyboard::Key key);
    void SetDown(sf::Keyboard::Key key);
    void SetLeft(sf::Keyboard::Key key);
    void SetRight(sf::Keyboard::Key key);
    void SetOK(sf::Keyboard::Key key);

private:
    sf::Keyboard::Key _up;
    sf::Keyboard::Key _down;
    sf::Keyboard::Key _left;
    sf::Keyboard::Key _right;
    sf::Keyboard::Key _ok;
};