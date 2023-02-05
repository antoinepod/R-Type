/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** main.cpp
*/

#include "graphics/gameLoop.cpp"

int main(int ac, char **av) {
    if (ac != 3) {
        std::cout << "Usage: ./client [IP] [PORT]." << std::endl;
        return -1;
    }
    gameLoop(av[1], av[2]);
    return 0;
}