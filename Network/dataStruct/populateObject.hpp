/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** populateObject.hpp
*/

#pragma once

#include "playerObject.hpp"
#include "enemyObject.hpp"

    namespace Network {
        std::pair<std::vector<Network::PlayerObject>, std::vector<Network::EnemyObject>> populatePlayerObject(std::pair<std::vector<Network::PlayerObject>, std::vector<Network::EnemyObject>> gameObject, int playerNumber, float x, float y) {;
            std::vector<Network::PlayerObject> playerObjectHolder = gameObject.first;
            std::vector<Network::EnemyObject> enemyObjectHolder = gameObject.second;
            Network::PlayerObject player;

            player.setX(x);
            player.setY(y);
            player.setCelerity(0.1);
            player.setHealth(1);
            player.setStrength(1);
            player.setPlayerNumber(playerNumber);
            player.setType(1);

            playerObjectHolder.push_back(player);
            return make_pair(playerObjectHolder, enemyObjectHolder);
        }

        std::pair<std::vector<Network::PlayerObject>, std::vector<Network::EnemyObject>> populateEnemyObject(std::pair<std::vector<Network::PlayerObject>, std::vector<Network::EnemyObject>> gameObject) {
            std::vector<Network::PlayerObject> playerObjectHolder = gameObject.first;
            std::vector<Network::EnemyObject> enemyObjectHolder = gameObject.second;
            Network::EnemyObject enemy;

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