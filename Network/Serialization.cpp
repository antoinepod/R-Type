/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** serialization.cpp
*/

#include "Serialization.hpp"

Network::Seria::Seria() = default;

Network::Seria::~Seria() = default;

void Network::Seria::S_erialize(std::vector<Network::GameObject> gameObject, boost::asio::streambuf *buf) {
    serialize(*buf, gameObject.size());
    for (auto& a : gameObject) {
        serialize(*buf, a.getX());
        serialize(*buf, a.getY());
        serialize(*buf, a.getCelerity());
        serialize(*buf, a.getHealth());
        serialize(*buf, a.getStrength());
        serialize(*buf, a.getPlayerNumber());
        serialize(*buf, a.getType());
    }
    //std::cout << "Serialized data size: " << buf->size() << std::endl;
}