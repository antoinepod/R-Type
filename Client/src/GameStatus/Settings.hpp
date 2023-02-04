/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-william.mallevays
** File description:
** Settings.hpp
*/

#pragma once

#include "IGameStatus.hpp"
#include "R-Type.hpp"


class Settings : public IGameStatus {
public:
    explicit Settings();
    ~Settings() override;

    void Display() override;
    GameStatus ManageInput(std::string &serverIp) override;

private:
    std::string _ip;
};

