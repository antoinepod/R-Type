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
    DrawText("Settings", 100, 100, 80, WHITE);
}

GameStatus Settings::ManageInput() {
    if (IsKeyPressed(KEY_ESCAPE))
        return GameStatus::MENU;

    return GameStatus::SETTINGS;
}
