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

    GameStatus ManageInput(sf::Event event, std::string &serverIp, Inputs &inputs) override;
    void Display(const std::shared_ptr<sf::RenderWindow>& window) override;

    GameStatus GetSelectedButton() const;

private:
    sf::Font _arcadeFont;
    std::vector<sf::Text> _buttons;
    sf::Text _title;
    sf::Text _serverIpInfo;
    unsigned int _selectedButton;
    std::string _serverIp;
};
