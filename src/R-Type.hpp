/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-william.mallevays
** File description:
** R-Type.hpp
*/

#pragma once

#include <raylib.h>
#include "GameStatus/IGameStatus.hpp"
#include <map>
#include <memory>

class RType {
public:
    RType();
    ~RType();

    void Start();

protected:
private:
    std::map<GameStatus, std::shared_ptr<IGameStatus>> _gameStatus;
    GameStatus _currentGameStatus;
};