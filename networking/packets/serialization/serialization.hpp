#pragma once

#include <vector>
#include <cstdlib>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include "../dataStruct/populateObject.hpp"

namespace RType {
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
                void S_erialize(std::pair<std::vector<RType::Network::PlayerObject>, std::vector<RType::Network::EnemyObject>> gameData, boost::asio::streambuf *buf) {
                    std::vector<RType::Network::PlayerObject> playerObject = gameData.first;
                    std::vector<RType::Network::EnemyObject> enemyObject = gameData.second;

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
}