/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** deserialization.hpp
*/

#pragma once

#include "dataStruct/playerObject.hpp"
#include "dataStruct/enemyObject.hpp"

    namespace Network {

        class Deseria {

        public:
            Deseria() {};
            ~Deseria() {};

            std::pair<std::vector<Network::PlayerObject>, std::vector<Network::EnemyObject>> D_eserialize(boost::array<char, 1024>& buffer) {
                Network::PlayerObject playerObject;
                Network::EnemyObject enemyObject;
                std::size_t pos = 0;
                std::size_t size = 0;
                std::vector<Network::PlayerObject> playerObjectHolder;
                std::vector<Network::EnemyObject> enemyObjectHolder;

                size = getMeta(buffer, pos);
                //std::cout << "the buffer size is: " << size << std::endl;
                for (int i = 0; i < size; i++) {
                    playerObject.setX(getFloatValue(buffer, pos));
                    playerObject.setY(getFloatValue(buffer, pos));
                    playerObject.setCelerity(getFloatValue(buffer, pos));
                    playerObject.setHealth(getIntValue(buffer, pos));
                    playerObject.setStrength(getIntValue(buffer, pos));
                    playerObject.setPlayerNumber(getIntValue(buffer, pos));
                    playerObject.setType(getIntValue(buffer, pos));
                    playerObjectHolder.push_back(playerObject);
                }
                size = getMeta(buffer, pos);
                for (int i = 0; i < size; i++) {
                    enemyObject.setX(getFloatValue(buffer, pos));
                    enemyObject.setY(getFloatValue(buffer, pos));
                    enemyObject.setCelerity(getFloatValue(buffer, pos));
                    enemyObject.setHealth(getIntValue(buffer, pos));
                    enemyObject.setStrength(getIntValue(buffer, pos));
                    enemyObject.setPlayerNumber(getIntValue(buffer, pos));
                    enemyObject.setType(getIntValue(buffer, pos));
                    enemyObjectHolder.push_back(enemyObject);
                }
                return make_pair(playerObjectHolder, enemyObjectHolder);
            };
            std::size_t getMeta(boost::array<char, 1024> buffer, std::size_t& pos) {
                std::size_t result = 0;
                std::memcpy(&result, buffer.data() + pos, sizeof(result));
                pos += sizeof(result);
                //std::cout << "size_t value: " << result << "and pos is: " << pos << std::endl;
                return result;
            }
            int getIntValue(boost::array<char, 1024> buffer, std::size_t& pos) {
                int result = 0;
                std::memcpy(&result, buffer.data() + pos, sizeof(result));
                pos += sizeof(result);
                ///std::cout << "int value: " << result << "and pos is: " << pos << std::endl;
                return result;
            }
            float getFloatValue(boost::array<char, 1024> buffer, std::size_t& pos) {
                float result = 0;
                std::memcpy(&result, buffer.data() + pos, sizeof(result));
                pos += sizeof(result);
                //std::cout << "double value: " << result << "and pos is: " << pos << std::endl;
                return result;
            }
        };
    }
