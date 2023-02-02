#pragma once

#include "../includes/network.hpp"

namespace RType {
    namespace Network {
        class UDPClient {
            public:
                UDPClient() {};
                ~UDPClient() {};
                void Run() {
                    boost::asio::ip::udp::socket socket = SocketFd();
                    boost::array<char, 1> send_buf  = {{ 48 }};
                    socket.send_to(boost::asio::buffer(send_buf), receiver_endpoint);

                    boost::array<char, 128> recv_buf;
                    boost::asio::ip::udp::endpoint sender_endpoint;
                    size_t len = socket.receive_from(
                            boost::asio::buffer(recv_buf), sender_endpoint);

                    std::cout.write(recv_buf.data(), len);
                    std::cout << "" << recv_buf.data() << std::endl;
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
        };
    }
}