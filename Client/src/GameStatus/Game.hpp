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

    // SFML functions
    GameStatus ManageInput(sf::Event event, std::string &serverIp) override;
    void Display(const std::shared_ptr<sf::RenderWindow>& window) override;

    // Server connection
    void ConnectToServer();

    // Object updates
    void UpdatePlayer(Network::Object & player);
    void UpdateEnemy(Network::Object & enemy);
    void UpdateBullet(Network::Object & bullet);
    void UpdatePowerUp(Network::Object & powerUp);

    // Timers
    void ShootTimer();

    std::atomic_bool isRunning;

private:
    std::map<Action, sf::Keyboard::Key> _input;

    sf::Font _arcadeFont;

    // Player assets
    sf::Texture _spaceShipTexture;
    sf::IntRect _spaceShipRect;
    sf::Sprite _spaceShip;

    // Enemy assets
    // TODO

    // Bullet assets
    sf::Texture _bulletTexture;
    sf::Sprite _bullet;
    bool _canShoot;

    // PowerUp assets
    // TODO

    std::vector<Network::Object> _objects;

    int _count;
    std::vector<std::thread> _threads;
    std::string _serverIp;

    boost::asio::io_service _tcpService;
    boost::asio::io_service _service;
    std::shared_ptr<boost::asio::ip::udp::socket> _socket;
    boost::asio::ip::udp::endpoint _serverEndpoint;

    int _playerId;
};