/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Game.hpp
*/

#pragma once

#include "IGameStatus.hpp"


class Game : public IGameStatus {
public:
    explicit Game();
    ~Game() override;

    void Display() override;
    GameStatus ManageInput() override;

private:
    Texture _spaceShip;
    Vector2 _spaceShipPos;
    Rectangle _spaceShipRec;
    int _count;
};

