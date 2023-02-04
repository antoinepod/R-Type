#pragma once

#include "playerObject.hpp"
#include "enemyObject.hpp"
#include <utility>

namespace RType {
    namespace Network {
        std::pair<std::vector<RType::Network::PlayerObject>, std::vector<RType::Network::EnemyObject>> populateObject() {
            RType::Network::GameObject test;
            RType::Network::PlayerObject playerOne;
            RType::Network::PlayerObject playerTwo;
            RType::Network::EnemyObject enemyOne;
            RType::Network::EnemyObject enemyTwo;
            std::vector<RType::Network::PlayerObject> playerObjectHolder;
            std::vector<RType::Network::EnemyObject> enemyObjectHolder;

            test.setX(0.1);
            test.setY(0.1);
            test.setCelerity(0.1);
            test.setHealth(1);
            test.setStrength(1);
            test.setPlayerNumber(1);
            test.setType(1);

            playerOne.setX(0.1);
            playerOne.setY(0.1);
            playerOne.setCelerity(0.1);
            playerOne.setHealth(1);
            playerOne.setStrength(1);
            playerOne.setPlayerNumber(1);
            playerOne.setType(1);
            
            playerTwo.setX(0.2);
            playerTwo.setY(0.2);
            playerTwo.setCelerity(0.2);
            playerTwo.setHealth(2);
            playerTwo.setStrength(2);
            playerTwo.setPlayerNumber(2);
            playerTwo.setType(1);

            enemyOne.setX(0.3);
            enemyOne.setY(0.3);
            enemyOne.setCelerity(0.3);
            enemyOne.setHealth(3);
            enemyOne.setStrength(3);
            enemyOne.setPlayerNumber(-1);
            enemyOne.setType(2);

            enemyTwo.setX(0.4);
            enemyTwo.setY(0.4);
            enemyTwo.setCelerity(0.4);
            enemyTwo.setHealth(4);
            enemyTwo.setStrength(4);
            enemyTwo.setType(2);
            enemyTwo.setPlayerNumber(-1);

            //std::cout << "test: " << test.getPlayerNumber() << std::endl;
            //std::cout << "playerOne: " << playerOne.getPlayerNumber() << std::endl;
            //std::cout << "playerTwo: " << playerTwo.getPlayerNumber() << std::endl;
            //std::cout << "enemyOne: " << enemyOne.getPlayerNumber() << std::endl;
            //std::cout << "enemyTwo: " << enemyTwo.getPlayerNumber() << std::endl;
            //playerObjectHolder.push_back(playerOne);
            //playerObjectHolder.push_back(playerTwo);
            //enemyObjectHolder.push_back(enemyOne);
            //enemyObjectHolder.push_back(enemyTwo);
            //for (auto& objects : playerObjectHolder) {
            //    std::cout << "Area: " << objects.getType() << std::endl;
            //}
            return make_pair(playerObjectHolder, enemyObjectHolder);
        }
    }
}