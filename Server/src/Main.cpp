/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-william.mallevays
** File description:
** Main.cpp
*/

#include "Server.hpp"


int main()
{
    boost::asio::io_service service;
    Server server(service);
    std::vector<std::thread> workerThreads;

    for (int i = 0; i < num_threads; i++)
        workerThreads.emplace_back([&service, &server]() { server.workerThread(service); });

    for (auto& t : workerThreads)
        t.join();

    return 0;
}
