/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-william.mallevays
** File description:
** Game.cpp
*/

#include <iostream>
#include "Game.hpp"

#include <filesystem>


Game::Game() {
    std::cout << "Current path = " << std::filesystem::current_path() << std::endl;
    _spaceShip = LoadTexture("assets/spaceShip.png");
    _spaceShipPos = {100, 420};
    _spaceShipRec = {132, 0, 66, 34};
    _count = 0;

    _ipStatus = false;
}

Game::~Game() {
}

void Game::Display() {
    ClearBackground(BLACK);
    if (!_ipStatus) {
        DrawText("Enter IP address:", 100, 100, 80, WHITE);
        DrawText(_ip.c_str(), 100, 200, 80, WHITE);
    } else {
        DrawTextureRec(_spaceShip, _spaceShipRec, _spaceShipPos, WHITE);
        DrawText(_serverIp.c_str(), 100, 100, 80, WHITE);
    }
}

GameStatus Game::ManageInput() {
    if (IsKeyPressed(KEY_ESCAPE))
        return GameStatus::MENU;

    if (!_ipStatus) {
        int key = GetCharPressed();

        while (key > 0) {
            if (key >= 32 && key <= 125)
                _ip.push_back(key);
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE) && !_ip.empty())
            _ip.pop_back();
        if (IsKeyPressed(KEY_ENTER))
            _ipStatus = true;
    } else {
        if (IsKeyDown(KEY_UP) && _spaceShipPos.y > 0) {
            _spaceShipPos.y -= 4;
            _count++;
            if (_count >= 10)
                _spaceShipRec.x = 264;
            else
                _spaceShipRec.x = 198;
        } else if (IsKeyDown(KEY_DOWN) && _spaceShipPos.y < 900 - 34) {
            _spaceShipPos.y += 4;
            _count++;
            if (_count >= 10)
                _spaceShipRec.x = 0;
            else
                _spaceShipRec.x = 66;
        } else {
            _spaceShipRec.x = 132;
            _count = 0;
        }
        if (IsKeyDown(KEY_LEFT) && _spaceShipPos.x > 0) {
            _spaceShipPos.x -= 4;
        }
        if (IsKeyDown(KEY_RIGHT) && _spaceShipPos.x < 1500 - 66) {
            _spaceShipPos.x += 4;
        }

        if (IsKeyPressed(KEY_F1))
            _spaceShipRec.y = 0;
        if (IsKeyPressed(KEY_F2))
            _spaceShipRec.y = 34;
        if (IsKeyPressed(KEY_F3))
            _spaceShipRec.y = 68;
        if (IsKeyPressed(KEY_F4))
            _spaceShipRec.y = 102;
        if (IsKeyPressed(KEY_F5))
            _spaceShipRec.y = 136;
    }

    return GameStatus::GAME;
}
