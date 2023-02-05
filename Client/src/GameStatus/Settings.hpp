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

    void Display(const std::shared_ptr<sf::RenderWindow>& window) override;
    GameStatus ManageInput(sf::Event event, std::string &serverIp) override;

private:
    std::string _ip;

    sf::Text _title;
    sf::Text _ipText;
    sf::Text _ipNumber;
};

