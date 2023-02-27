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
    GameStatus ManageInput(sf::Event event, std::string &serverIp, Inputs &inputs) override;
    void Display(const std::shared_ptr<sf::RenderWindow>& window) override;

    // Server connection
    void ConnectToServer();

    // Object updates
    void UpdatePlayer(const std::shared_ptr<sf::RenderWindow>& window, Network::Object & player);
    void UpdateEnemy(const std::shared_ptr<sf::RenderWindow>& window, Network::Object & enemy);
    void UpdateBullet(const std::shared_ptr<sf::RenderWindow>& window, Network::Object & bullet);
    void UpdatePowerUp(const std::shared_ptr<sf::RenderWindow>& window, Network::Object & powerUp);
    void UpdateExplosion(const std::shared_ptr<sf::RenderWindow> & window, Network::Object & explosion);

    void UpdateData(std::vector<Network::Object> objects);
        // Timers
    void ShootTimer();

    std::atomic_bool isRunning;

private:
    sf::Music _gameMusic;
    sf::Font _arcadeFont;

    bool _drawError;
    sf::Text _errorText;

    // Player assets
    sf::Texture _spaceShipTexture;
    sf::IntRect _spaceShipRect;
    sf::Sprite _spaceShip;
    sf::Text _playerName;

    // Enemy assets
    std::vector<sf::Sprite> _enemies;
    std::vector<std::shared_ptr<sf::Texture>> _enemyTextures;
    std::vector<float> _enemiesScale;

    // Bullet assets
    std::map<BulletType, sf::Sprite> _bullet;
    std::map<BulletType ,std::shared_ptr<sf::Texture>> _bulletTexture;
    bool _canShoot;

    // PowerUp assets
    // TODO

    // Explosion assets
    std::map<ExplosionType, sf::Sprite> _explosion;
    std::map<ExplosionType ,std::shared_ptr<sf::Texture>> _explosionTexture;
    sf::IntRect _explosionRect;
    int _explosionTmp;

    std::vector<Network::Object> _objects;

    std::vector<std::thread> _threads;
    std::string _serverIp;

    std::mutex _mutex;

    boost::asio::io_service _tcpService;
    boost::asio::io_service _service;
    std::shared_ptr<boost::asio::ip::udp::socket> _socket;
    boost::asio::ip::udp::endpoint _serverEndpoint;

    sf::Sound _shootSound;
    sf::SoundBuffer _shootSoundBuffer;

    int _playerId;
};