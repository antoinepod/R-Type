/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-william.mallevays
** File description:
** R-Type.cpp
*/

#include "R-Type.hpp"


RType::RType() {
    InitWindow(1500, 900, "R-Type window");
    SetTargetFPS(60);
    SetExitKey(KEY_A);

    _gameStatus[GameStatus::MENU] = std::make_shared<Menu>();
    _gameStatus[GameStatus::GAME] = std::make_shared<Game>();
    _gameStatus[GameStatus::SETTINGS] = std::make_shared<Settings>();
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
