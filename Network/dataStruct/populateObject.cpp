/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** populateObject.cpp
*/


#include "populateObject.hpp"

Network::Populate::Populate() = default;

Network::Populate::~Populate() = default;

Network::PlayerObject Network::Populate::PlayerObject(int playerNumber, float x, float y) {;
    Network::PlayerObject player;

    player.setX(x);
    player.setY(y);
    player.setCelerity(0.1);
    player.setHealth(1);
    player.setStrength(1);
    player.setPlayerNumber(playerNumber);
    player.setType(1);

    return player;
}