/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** serialization.hpp
*/

#pragma once

#include "dataStruct/populateObject.hpp"

    namespace Network {
        template <typename T>
        void serialize(boost::asio::streambuf& buf, const T& t) {
            std::ostream os(&buf);
            //std::cout << "size is: " << sizeof(t) << std::endl;
            os.write(reinterpret_cast<const char*>(&t), sizeof(t));
        }

        class Seria {
        public:
            Seria() {};
            ~Seria() {};
            void S_erialize(std::pair<std::vector<Network::PlayerObject>, std::vector<Network::EnemyObject>> gameData, boost::asio::streambuf *buf) {
                std::vector<Network::PlayerObject> playerObject = gameData.first;
                std::vector<Network::EnemyObject> enemyObject = gameData.second;

                serialize(*buf, playerObject.size());
                for (auto& a : playerObject) {
                    serialize(*buf, a.getX());
                    serialize(*buf, a.getY());
                    serialize(*buf, a.getCelerity());
                    serialize(*buf, a.getHealth());
                    serialize(*buf, a.getStrength());
                    serialize(*buf, a.getPlayerNumber());
                    serialize(*buf, a.getType());
                }
                serialize(*buf, enemyObject.size());
                for (auto& a : enemyObject) {
                    serialize(*buf, a.getX());
                    serialize(*buf, a.getY());
                    serialize(*buf, a.getCelerity());
                    serialize(*buf, a.getHealth());
                    serialize(*buf, a.getStrength());
                    serialize(*buf, a.getPlayerNumber());
                    serialize(*buf, a.getType());
                }
                //std::cout << "Serialized data size: " << buf->size() << std::endl;
            };
        };
    }