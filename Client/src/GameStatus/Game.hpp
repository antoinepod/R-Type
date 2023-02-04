/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-william.mallevays
** File description:
** Game.hpp
*/

#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include "IGameStatus.hpp"
#include "R-Type.hpp"



class Game : public IGameStatus {
public:
    explicit Game();
    ~Game() override;

    void Display() override;
    GameStatus ManageInput(std::string &serverIp) override;

    void connectToServer();
    void receiveData();

private:
    Texture _spaceShip;
    Vector2 _spaceShipPos;
    Rectangle _spaceShipRec;
    int _count;
    std::atomic_bool _isRunning;
    std::thread _thread;
    std::string _serverIp;
};

