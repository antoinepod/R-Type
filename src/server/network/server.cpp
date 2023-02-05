/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** server.cpp
*/

#include "../../../includes/networking/UDP/UDPServer.hpp"

void server()
{
    try
    {
        boost::asio::io_context io_context;
        udp_server server(io_context);
        std::thread t([&io_context] { io_context.run(); });
        while (true) {
        //    std::cout << "IS OK" << std::endl;
        //    sleep(5);
            //if udp_server.()
            //if (server.gameObject.second.size() == 0)
            //    server.gameObject = RType::Network::populateEnemyObject(server.gameObject);
        }
        io_context.stop();
        t.join();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}
