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

    GameStatus ManageInput(sf::Event event, std::string &serverIp, Inputs &inputs) override;
    void Display(const std::shared_ptr<sf::RenderWindow>& window) override;

private:
    std::string _ip;

    sf::Font _arcadeFont;
    sf::Text _title;

    std::vector<sf::Text> _texts;

    float _volume;

    int _selectedText;
};

