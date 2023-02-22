/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-william.mallevays
** File description:
** IGameStatus.hpp
*/

#pragma once

#include <vector>
#include <string>
#include <memory>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <iostream>
#include <thread>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

#include "Data/Enums.hpp"

#define SCREEN_WIDTH 1500
#define SCREEN_HEIGHT 900


enum GameStatus {
    MENU,
    GAME,
    SETTINGS,
    CLOSE
};

class IGameStatus {
public:
    virtual ~IGameStatus() = default;

    virtual void Display(const std::shared_ptr<sf::RenderWindow>& window) = 0;
    virtual GameStatus ManageInput(sf::Event event, std::string &serverIp) = 0;
};
