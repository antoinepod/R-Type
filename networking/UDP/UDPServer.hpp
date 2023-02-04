#pragma once

#include "../interfaces/INetwork.hpp"

namespace RType {
    namespace Network {
        class UDPServer {
            public:
                UDPServer() {};
                ~UDPServer() {};
                void Run() {
                    boost::asio::ip::udp::socket socket = this->SocketFd();
                    for (;;) {
                        boost::array<char, 1024> recv_buf;
                        boost::asio::ip::udp::endpoint remote_endpoint;

                        socket.receive_from(boost::asio::buffer(recv_buf), remote_endpoint);
                        std::string message = make_daytime_string();

                        boost::system::error_code ignored_error;
                        socket.send_to(boost::asio::buffer(message), remote_endpoint, 0, ignored_error);
                    }
                };
                boost::asio::ip::udp::socket SocketFd() {
                    boost::asio::ip::udp::socket socket(io_context, boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 8080));
                    return socket;
                };
                std::string make_daytime_string() {
                    using namespace std; // For time_t, time and ctime;
                    time_t now = time(0);
                    return ctime(&now);
                };

            public:
                boost::asio::io_context io_context;
        };
    }
}