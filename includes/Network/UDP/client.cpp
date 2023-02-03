#include <iostream>
#include <chrono>
#include <thread>
#include <boost/asio.hpp>

using namespace boost::asio;
using namespace boost::asio::ip;

const std::string server_address = "127.0.0.1";
const int port_num = 8080;

int main()
{
    io_service service;
    udp::socket socket(service, udp::endpoint(udp::v4(), 0));
    udp::endpoint server_endpoint = *udp::resolver(service).resolve({udp::v4(), server_address, std::to_string(port_num)});

    while (true)
    {
        std::vector<int> message = {1, 2, 3, 4, 5};
        socket.send_to(boost::asio::buffer(message), server_endpoint);

        std::cout << "Sent message to server: ";
        for (auto& number : message)
            std::cout << number << " ";
        std::cout << std::endl;

        std::array<char, 1024> recv_buf;
        udp::endpoint sender_endpoint;
        size_t bytes_recvd = socket.receive_from(buffer(recv_buf), sender_endpoint);

        std::cout << "Received message from " << sender_endpoint << ": ";
        std::cout.write(recv_buf.data(), bytes_recvd);
        std::cout << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    return 0;
}