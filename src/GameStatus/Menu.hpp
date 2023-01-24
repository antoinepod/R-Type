/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-william.mallevays
** File description:
** Menu.hpp
*/

#pragma once

#include "IGameStatus.hpp"


class Menu : public IGameStatus {
public:
    explicit Menu();
    ~Menu() override;

    void Display() override;
    GameStatus ManageInput() override;

private:
    std::vector<std::string> _buttons;
    unsigned int _selectedButton;
    Font _font;
};
