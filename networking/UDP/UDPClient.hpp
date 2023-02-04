#pragma once

#include "../interfaces/INetwork.hpp"
#include "../packets/serialization/serialization.hpp"
#include "../packets/deserialization/deserialization.hpp"

namespace RType {
    namespace Network {
        class UDPClient {
            public:
                UDPClient() {};
                ~UDPClient() {};
                void Run() {
                    boost::asio::ip::udp::socket socket = SocketFd();
                    boost::array<char, 1024> send_buf  = {{ 48 }};
                    socket.send_to(boost::asio::buffer(send_buf), receiver_endpoint);

                    boost::array<char, 1024> recv_buf;
                    boost::asio::ip::udp::endpoint sender_endpoint;
                    size_t len = socket.receive_from(boost::asio::buffer(recv_buf), sender_endpoint);
                    recv_buf[len] = '\0';

                    //std::cout << "recv_buf size is :" << recv_buf.size << std::endl;
                    //std::cout.write(recv_buf.data(), len);
                    //std::cout << "the data is: " << strlen(recv_buf.data()) << std::endl;
                    //std::cout << "recv_buf size is: " << recv_buf.size << std::endl;
                    //std::cout << "size_t lenreceived is: " << len << std::endl;
                    gameData = deseria.D_eserialize(recv_buf);
                    //std::vector<RType::Network::PlayerObject> playerObject = gameData.first;
                    //std::vector<RType::Network::EnemyObject> enemyObject = gameData.second;
                    //for (auto& i : playerObject) {
                    //    std::cout << "Player object get type: " << i.getType() << std::endl;
                    //}
                    //for (auto& i : enemyObject) {
                    //    std::cout << "Enemy object get type: " << i.getType() << std::endl;
                    //}
                };
                boost::asio::ip::udp::socket SocketFd() {
                    boost::asio::ip::udp::resolver resolver(io_context);
                    receiver_endpoint = *resolver.resolve(boost::asio::ip::udp::v4(), this->host, "8080").begin();

                    boost::asio::ip::udp::socket socket(io_context);
                    socket.open(boost::asio::ip::udp::v4());
                    return socket;
                };

            public:
                boost::asio::io_context io_context;
                boost::asio::ip::udp::endpoint receiver_endpoint;
                std::string host = "127.0.0.1";
                std::pair<std::vector<RType::Network::PlayerObject>, std::vector<RType::Network::EnemyObject>> gameData;
                RType::Network::Deseria deseria;
        };
    }
}