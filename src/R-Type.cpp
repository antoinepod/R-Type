/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-william.mallevays
** File description:
** R-Type.cpp
*/

#include "R-Type.hpp"
#include "GameStatus/Menu.hpp"

RType::RType() {
    InitWindow(600, 600, "R-Type window");
    SetTargetFPS(60);

    _gameStatus[GameStatus::MENU] = std::make_shared<Menu>();
    _currentGameStatus = GameStatus::MENU;
}

RType::~RType() {
    CloseWindow();
}

void RType::Start() {
    while (!WindowShouldClose())
    {
        _currentGameStatus = _gameStatus[_currentGameStatus]->ManageInput();

        if (_currentGameStatus == GameStatus::CLOSE)
            break;

        BeginDrawing();
        _gameStatus[_currentGameStatus]->Display();
        DrawFPS(10, 10);
        EndDrawing();
    }
}