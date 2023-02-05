/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** populateObject.hpp
*/

#pragma once

#include "playerObject.hpp"
#include "enemyObject.hpp"

namespace RType {
    namespace Network {
        std::pair<std::vector<RType::Network::PlayerObject>, std::vector<RType::Network::EnemyObject>> populatePlayerObject(std::pair<std::vector<RType::Network::PlayerObject>, std::vector<RType::Network::EnemyObject>> gameObject) {
            std::vector<RType::Network::PlayerObject> playerObjectHolder = gameObject.first;
            std::vector<RType::Network::EnemyObject> enemyObjectHolder = gameObject.second;
            RType::Network::PlayerObject player;

            player.setX(0.1);
            player.setY(0.1);
            player.setCelerity(0.1);
            player.setHealth(1);
            player.setStrength(1);
            player.setPlayerNumber(1);
            player.setType(1);

            playerObjectHolder.push_back(player);
            return make_pair(playerObjectHolder, enemyObjectHolder);
        }

        std::pair<std::vector<RType::Network::PlayerObject>, std::vector<RType::Network::EnemyObject>> populateEnemyObject(std::pair<std::vector<RType::Network::PlayerObject>, std::vector<RType::Network::EnemyObject>> gameObject) {
            std::vector<RType::Network::PlayerObject> playerObjectHolder = gameObject.first;
            std::vector<RType::Network::EnemyObject> enemyObjectHolder = gameObject.second;
            RType::Network::EnemyObject enemy;

            enemy.setX(0.4);
            enemy.setY(0.4);
            enemy.setCelerity(0.4);
            enemy.setHealth(4);
            enemy.setStrength(4);
            enemy.setPlayerNumber(-1);
            enemy.setType(2);

            enemyObjectHolder.push_back(enemy);
            return make_pair(playerObjectHolder, enemyObjectHolder);
        }
    }
}