/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-william.mallevays
** File description:
** Main.cpp
*/

#include "R-Type.hpp"

int main() {
    std::shared_ptr<RType> game = std::make_shared<RType>();

    game->Start();
    return 0;
}