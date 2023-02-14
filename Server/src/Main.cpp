///*
//** EPITECH PROJECT, 2023
//** B-CPP-500-LIL-5-2-rtype-william.mallevays
//** File description:
//** Main.cpp
//*/
//
//#include "Server.hpp"
//
//
//int main()
//{
//    boost::asio::io_service service;
//    Server server(service);
//    std::vector<std::thread> workerThreads;
//
//    for (int i = 0; i < num_threads; i++)
//        workerThreads.emplace_back([&service, &server]() { server.workerThread(service); });
//
//    for (auto& t : workerThreads)
//        t.join();
//
//    return 0;
//}

/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** server.cpp
*/

#include "UDPServer.hpp"

int main()
{
    try
    {
        boost::asio::io_context io_context;
        UDPServer server(io_context);
        std::thread t([&io_context] { io_context.run(); });
        while (true) {
            //    std::cout << "IS OK" << std::endl;
            //    sleep(5);
            //if udp_server.()
            //if (server.gameObject.second.size() == 0)
            //    server.gameObject = Network::populateEnemyObject(server.gameObject);
        }
        io_context.stop();
        t.join();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

