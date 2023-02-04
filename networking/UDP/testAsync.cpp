#include "UDPAsyncServer.hpp"
#include <thread>         // std::thread

int main()
{
    try
    {
        boost::asio::io_context io_context;
        udp_server server(io_context);
        std::thread t([&io_context] { io_context.run(); });
        for(int i = 0; i != 100; i++) {
            //std::cout << "IS OK" << std::endl;
            sleep(5);
        }
        io_context.stop();
        t.join();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
