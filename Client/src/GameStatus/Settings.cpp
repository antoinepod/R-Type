/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-william.mallevays
** File description:
** Settings.cpp
*/

#include "Settings.hpp"


Settings::Settings() {
}

Settings::~Settings() {
}

void Settings::Display() {
    ClearBackground(BLACK);
    DrawText("Settings", 750 - (MeasureText("Settings", 60) / 2), 50, 60, WHITE);

    DrawText("Server IP address :", 50, 200, 40, WHITE);
    DrawText(_ip.c_str(), 500, 200, 40, WHITE);

}

GameStatus Settings::ManageInput(std::string &serverIp) {
    _ip = serverIp;
    
    if (IsKeyPressed(KEY_ESCAPE))
        return GameStatus::MENU;

    int key = GetCharPressed();

    while (key > 0) {
        if (key >= 32 && key <= 125)
            serverIp.push_back(key);
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) && !_ip.empty())
        serverIp.pop_back();

    return GameStatus::SETTINGS;
}
