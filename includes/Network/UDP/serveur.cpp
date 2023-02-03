#include <iostream>
#include <vector>
#include <thread>
#include <boost/asio.hpp>

using namespace boost::asio;
using namespace boost::asio::ip;

const int num_threads = 4;
const int port_num = 8080;

void worker_thread(io_service& service)
{
    service.run();
}

class Server
{
public:
    Server(io_service& service) : socket(service, udp::endpoint(udp::v4(), port_num))
    {
        start_receive();
    }

    void start_receive()
    {
        socket.async_receive_from(buffer(recv_buf), remote_endpoint, [this](const boost::system::error_code& ec, size_t bytes_recvd) {
            if (!ec && bytes_recvd > 0) {
                handle_receive(bytes_recvd);
            } else {
                std::cout << "Error: " << ec.message() << std::endl;
            }
            start_receive();
        });
    }

    void handle_receive(size_t bytes_recvd)
    {
        std::cout << "Received message from " << remote_endpoint << ": ";
        std::vector<int> recvd_vec(bytes_recvd / sizeof(int));
        memcpy(recvd_vec.data(), recv_buf.data(), bytes_recvd);
        for (int num : recvd_vec)  {
            std::cout << num << " ";
        }
        std::cout << std::endl;

        socket.async_send_to(buffer("Hello from the server"), remote_endpoint, [this](const boost::system::error_code& ec, size_t bytes_sent) {
            if (!ec) {
                std::cout << "Sent message to " << remote_endpoint << std::endl;
            } else {
                std::cout << "Error: " << ec.message() << std::endl;
            }
        });
    }

private:
    udp::socket socket;
    udp::endpoint remote_endpoint;
    std::array<char, 1024> recv_buf;
};

int main()
{
    io_service service;
    Server server(service);
    std::vector<std::thread> worker_threads;

    for (int i = 0; i < num_threads; i++) {
        worker_threads.emplace_back([&service]() { worker_thread(service); });
    }

    for (auto& t : worker_threads) {
        t.join();
    }

    return 0;
}
