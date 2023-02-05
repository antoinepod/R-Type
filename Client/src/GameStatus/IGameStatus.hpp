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

#define SCREEN_WIDTH 1500
#define SCREEN_HEIGHT 900

#define MOVE_UP sf::Keyboard::Up
#define MOVE_DOWN sf::Keyboard::Down
#define MOVE_LEFT sf::Keyboard::Left
#define MOVE_RIGHT sf::Keyboard::Right


enum GameStatus {
    MENU,
    GAME,
    SETTINGS,
    CLOSE
};

enum Actions {
    NONE = 0,
    UP = 2,
    RIGHT = 4,
    DOWN = 8,
    LEFT = 16,
    EVENT = 32
};

enum Events {
    SHOT = 64,
    QUIT = 128
};

class IGameStatus {
public:
    virtual ~IGameStatus() = default;

    virtual void Display(const std::shared_ptr<sf::RenderWindow>& window) = 0;
    virtual GameStatus ManageInput(sf::Event event, std::string &serverIp) = 0;
};
