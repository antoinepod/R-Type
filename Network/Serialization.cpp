/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** serialization.cpp
*/

#include "Serialization.hpp"


void Network::Seria::S_erialize(std::vector<Network::Object> & gameObject, boost::asio::streambuf *buf) {
    serialize(*buf, gameObject.size());
    for (auto& a : gameObject) {
        std::cout << "ggggObject: " << a.getType() << " id:" << a.getId() << " pos: " << a.getX() << " " << a.getY() << std::endl;
        // TODO
        serialize(*buf, a.getGameState());
        serialize(*buf, a.getX());
        serialize(*buf, a.getY());
        serialize(*buf, a.getCelerity());
        serialize(*buf, a.getHealth());
        serialize(*buf, a.getStrength());
        serialize(*buf, a.getId());
        serialize(*buf, a.getType());
        serialize(*buf, a.getFrame());
        serialize(*buf, a.getExplosion());
        serialize(*buf, a.getBullet());
        serialize(*buf, a.getSound());
        serialize(*buf, a.getEnemy());
        serialize(*buf, a.getFullHealth());
    }
}