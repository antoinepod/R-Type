/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-william.mallevays
** File description:
** Game.hpp
*/

#pragma once

#include "IGameStatus.hpp"
#include "Deserialization.hpp"


class Game : public IGameStatus {
public:
    explicit Game();
    ~Game() override;

    void Display(const std::shared_ptr<sf::RenderWindow>& window) override;
    GameStatus ManageInput(sf::Event event, std::string &serverIp) override;

    void ConnectToServer();

    std::atomic_bool isRunning;

private:
    sf::Font _arcadeFont;

    sf::Texture _spaceShipTexture;
    sf::Sprite _spaceShip;

    std::vector<Network::Object> _objects;

    int _count;
    std::thread _thread;
    std::string _serverIp;

    boost::asio::io_service _tcpService;
    boost::asio::io_service _service;
    std::shared_ptr<boost::asio::ip::udp::socket> _socket;
    boost::asio::ip::udp::endpoint _serverEndpoint;

    int _playerId;
};