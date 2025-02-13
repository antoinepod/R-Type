/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** UDPServer.hpp
*/

#pragma once

#include "Serialization.hpp"
#include "Deserialization.hpp"

class UDPServer
{
public:
    explicit UDPServer(boost::asio::io_context& io_context);
    ~UDPServer();

    void StartReceive();
    void Receive(const boost::system::error_code& error,std::size_t);
    void Send(boost::shared_ptr<std::string>,const boost::system::error_code&,std::size_t);

    int FindPlayer(int id);

    // Create GameObjects
    void CreateGameState();
    void CreatePlayer(const std::string& ip, int id, const std::string& name);
    void CreateEnemy(EnemyType type, float x, float y);
    void CreateBullet(Network::Object sender, BulletType bulletType);
    void CreateExplosion(ExplosionType explosionType, float x, float y);
    void CreateSound(SoundType soundType);

    // Update GameObjects
    void UpdateGame();
    void UpdateGameState(Network::Object & gameState);
    void UpdateEnemy(Network::Object & bullet);
    void UpdateBullet(Network::Object & bullet);
    void UpdatePowerUp(Network::Object & powerUp);
    void UpdateExplosion(Network::Object & explosion);
    void UpdateSound(Network::Object & sound);

    bool CheckCollision(Network::Object & object, Network::Object & bullet);
    void KillObject(Network::Object object);

    void Level_1(Network::Object & gameState);
    void Level_2(Network::Object & gameState);
    void Level_3(Network::Object & gameState);
    void UpdateLevel_1(Network::Object & gameState);
    void UpdateLevel_2(Network::Object & gameState);
    void UpdateLevel_3(Network::Object & gameState);

private:
    std::vector<Network::Object> _gameObject;
    std::shared_ptr<boost::asio::deadline_timer> _timer;
    int p_Id = 0;
    boost::asio::ip::udp::socket _socket;
    boost::asio::ip::udp::endpoint _remoteEndpoint;
    boost::array<unsigned int, 1> _recvBuffer;
    boost::asio::streambuf _buf;
    std::vector<std::thread> _threadPool;
    std::map<std::string, int> _myMap;
    std::mutex _mutex;
    std::map<int, int> _playerFrames;
    std::map<int, int> _explosionFrames;

    int _nbEnemy;

    int _bulletId = 0;
    int _explosionId = 0;
};
