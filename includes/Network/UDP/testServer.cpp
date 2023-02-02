#include "UDPServer.hpp"
#include <thread>         // std::thread

int main()
{
    try
    {
        boost::asio::io_context io_context;
        udp_server server(io_context);
        //io_context.run();
        std::thread t([&io_context] { io_context.run(); });
        for(int i = 0; i != 20; i++) {
            std::cout << "\"GAME LOOP\"" << std::endl;
            sleep(5);
        }
        t.join();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}
