/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-william.mallevays
** File description:
** IGameStatus.hpp
*/

#pragma once

#include <raylib.h>
#include <vector>
#include <string>

enum GameStatus {
    MENU,
    GAME,
    SETTINGS,
    CLOSE
};

class IGameStatus {
public:
    virtual ~IGameStatus() = default;

    virtual void Display() = 0;
    virtual GameStatus ManageInput() = 0;

};
