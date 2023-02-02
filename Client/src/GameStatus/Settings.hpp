/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-william.mallevays
** File description:
** Settings.hpp
*/

#pragma once

#include "IGameStatus.hpp"


class Settings : public IGameStatus {
public:
    explicit Settings();
    ~Settings() override;

    void Display() override;
    GameStatus ManageInput() override;

private:
};

