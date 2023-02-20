/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** PopulateObject.cpp
*/

#include "PopulateObject.hpp"


Network::Player Network::Populate::Player(int playerNumber, float x, float y) {;
    Network::Player player;

    player.setX(x);
    player.setY(y);
    player.setCelerity(0.1);
    player.setHealth(1);
    player.setStrength(1);
    player.setId(playerNumber);
    player.setType(ObjectType::PLAYER);

    return player;
}