/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-william.mallevays
** File description:
** Game.hpp
*/

#pragma once

#include "IGameStatus.hpp"


class Game : public IGameStatus {
public:
    explicit Game();
    ~Game() override;

    void Display(const std::shared_ptr<sf::RenderWindow>& window) override;
    GameStatus ManageInput(sf::Event event, std::string &serverIp) override;

    void connectToServer();
    void receiveData();

private:
    sf::Sprite _spaceShip;
    sf::Texture _spaceShipTexture;
    sf::Vector2f _spaceShipPos;
    sf::IntRect _spaceShipRect;
    int _count;
    std::atomic_bool _isRunning;
    std::thread _thread;
    std::string _serverIp;
};

