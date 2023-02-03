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
    std::vector<std::thread> worker_threads;

    for (int i = 0; i < num_threads; i++) {
        worker_threads.emplace_back([&service, &server]() { server.worker_thread(service); });
    }

    for (auto& t : worker_threads) {
        t.join();
    }

    return 0;
}
