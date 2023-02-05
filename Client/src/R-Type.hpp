/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-william.mallevays
** File description:
** R-Type.hpp
*/

#pragma once

#include <map>
#include <memory>

#include "GameStatus/IGameStatus.hpp"
#include "Menu.hpp"
#include "Game.hpp"
#include "Settings.hpp"



class RType {
public:
    RType();
    ~RType();

    void Start();
    void DrawFps();

protected:
private:
    std::map<GameStatus, std::shared_ptr<IGameStatus>> _gameStatus;
    GameStatus _currentGameStatus;

    std::shared_ptr<sf::RenderWindow> _window;

    std::string _serverIp;

    sf::Font _arcadeFont;

    sf::Clock _clock;
    float _currentTime;
    float _fps;
    sf::Text _fpsText;
};