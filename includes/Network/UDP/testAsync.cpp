#include "UDPAsyncServer.hpp"
#include <thread>         // std::thread

int main()
{
    try
    {
        boost::asio::io_context io_context;
        udp_server server(io_context);
        //io_context.run();
        std::thread t([&io_context] { io_context.run(); });
        for(int i = 0; i != 10; i++) {
            std::cout << "IS OK" << std::endl;
            sleep(3);
        }
        t.join();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    //std::thread first(io_context.run());
    return 0;
}
