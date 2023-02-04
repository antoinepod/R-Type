/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-william.mallevays
** File description:
** Menu.cpp
*/

#include "Menu.hpp"

Menu::Menu() {
    _buttons = {"Play", "Settings", "Quit"};
    _selectedButton = 0;
    _serverIp = "";
}

Menu::~Menu() {
}

void Menu::Display() {
    ClearBackground(BLACK);
    DrawText("R-Type", 750 - (MeasureText("R-Type", 80) / 2), 200, 80, WHITE);

    for (int i = 0; i < _buttons.size(); i++) {
        if (i == _selectedButton)
            DrawText(_buttons[i].c_str(), 750 - (MeasureText(_buttons[i].c_str(), 40) / 2), 450 + (i * 100), 40, BLUE);
        else
            DrawText(_buttons[i].c_str(), 750 - (MeasureText(_buttons[i].c_str(), 40) / 2), 450 + (i * 100), 40, WHITE);
    }

    if (_selectedButton == 0) {
        if (_serverIp.empty())
            DrawText("Server IP not set, please go to settings.", 750 - (MeasureText("(Server IP not set, please go to Settings)",20) / 2),500, 20, GRAY);
        else
            DrawText(_serverIp.c_str(), 750 - (MeasureText(_serverIp.c_str(),20) / 2),500, 20, GRAY);
    }
}

GameStatus Menu::ManageInput(std::string &serverIp) {
    _serverIp = serverIp;

    if (IsKeyPressed(KEY_UP) && _selectedButton > 0)
        _selectedButton--;
    if (IsKeyPressed(KEY_DOWN) && _selectedButton < _buttons.size() - 1)
        _selectedButton++;
    if (IsKeyPressed(KEY_ENTER)) {
        switch (_selectedButton) {
            case 0:
                if (_serverIp.empty())
                    break;
                else
                    return GameStatus::GAME;
            case 1:
                return GameStatus::SETTINGS;
            case 2:
                return GameStatus::CLOSE;
            default:
                break;
        }
    }
    return GameStatus::MENU;
}

