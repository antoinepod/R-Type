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
                os.write(reinterpret_cast<const char*>(&t), sizeof(t));
            }

        class Seria {
            public:
                Seria() {};
                ~Seria() {};
                boost::asio::streambuf &S_erialize(std::pair<std::vector<RType::Network::PlayerObject>, std::vector<RType::Network::EnemyObject>> gameData) {
                    std::vector<RType::Network::PlayerObject> playerObject = gameData.first;
                    std::vector<RType::Network::EnemyObject> enemyObject = gameData.second;

                    serialize(buf, playerObject.max_size());
                    for (auto& a : playerObject) {
                        serialize(buf, a.getX());
                        serialize(buf, a.getY());
                        serialize(buf, a.getCelerity());
                        serialize(buf, a.getHealth());
                        serialize(buf, a.getStrength());
                        serialize(buf, a.getPlayerNumber());
                    }

                    serialize(buf, enemyObject.max_size());
                    for (auto& a : enemyObject) {
                        serialize(buf, a.getX());
                        serialize(buf, a.getY());
                        serialize(buf, a.getCelerity());
                        serialize(buf, a.getHealth());
                        serialize(buf, a.getStrength());
                        serialize(buf, a.getPlayerNumber());
                    }

                    std::cout << "Serialized data size: " << buf.size() << std::endl;
                    return buf;
                };

            protected:
                boost::asio::streambuf buf;
                //std::vector<>
        };
    }
}