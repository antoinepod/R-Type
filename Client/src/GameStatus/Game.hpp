/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-william.mallevays
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

    std::string _serverIp;
    bool _ipStatus;

    std::string _ip;

private:
    Texture _spaceShip;
    Vector2 _spaceShipPos;
    Rectangle _spaceShipRec;
    int _count;
};

