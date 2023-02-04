#pragma once

#include <vector>
#include <cstdlib>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "../dataStruct/playerObject.hpp"
#include "../dataStruct/enemyObject.hpp"

namespace RType {
    namespace Network {

        class Deseria {

            public: 
                Deseria() {};
                ~Deseria() {};

                std::pair<std::vector<RType::Network::PlayerObject>, std::vector<RType::Network::EnemyObject>> D_eserialize(boost::array<char, 1024> buffer) {
                    RType::Network::PlayerObject playerObject;
                    RType::Network::EnemyObject enemyObject;
                    std::size_t pos = 0;
                    std::size_t size = 0;
                    std::vector<RType::Network::PlayerObject> playerObjectHolder;
                    std::vector<RType::Network::EnemyObject> enemyObjectHolder;

                    size = getMeta(&buffer, pos);
                    for (int i = 0; i < size; i++) {
                        playerObject.setX(getDoubleValue(&buffer, pos));
                        playerObject.setY(getDoubleValue(&buffer, pos));
                        playerObject.setCelerity(getDoubleValue(&buffer, pos));
                        playerObject.setHealth(getDoubleValue(&buffer, pos));
                        playerObject.setStrength(getDoubleValue(&buffer, pos));
                        playerObject.setPlayerNumber(getDoubleValue(&buffer, pos));
                        playerObjectHolder.push_back(playerObject);
                    }
                    size = getMeta(&buffer, pos);
                    for (int i = 0; i < size; i++) {
                        enemyObject.setX(getDoubleValue(&buffer, pos));
                        enemyObject.setY(getDoubleValue(&buffer, pos));
                        enemyObject.setCelerity(getDoubleValue(&buffer, pos));
                        enemyObject.setHealth(getDoubleValue(&buffer, pos));
                        enemyObject.setStrength(getDoubleValue(&buffer, pos));
                        enemyObject.setPlayerNumber(getDoubleValue(&buffer, pos));
                        enemyObjectHolder.push_back(enemyObject);
                    }
                    return make_pair(playerObjectHolder, enemyObjectHolder);
                };
                std::size_t getMeta(boost::array<char, 1024> *buffer, std::size_t& pos) {
                    std::size_t result;
                    std::memcpy(&result, buffer + pos, sizeof(result));
                    pos += sizeof(result);
                    return result;
                }
                int getIntValue(boost::array<char, 1024> *buffer, std::size_t pos) {
                    int result;
                    std::memcpy(&result, buffer + pos, sizeof(result));
                    pos += sizeof(result);
                    return result;
                }
                double getDoubleValue(boost::array<char, 1024> *buffer, std::size_t pos) {
                    double result;
                    std::memcpy(&result, buffer + pos, sizeof(result));
                    pos += sizeof(result);
                    return result;
                }
        };
    }
}