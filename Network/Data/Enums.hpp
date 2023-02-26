/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Enums.hpp
*/

#pragma once

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>

#define THREADS_NBR 4

enum Action {
    NONE = 0,
    UP = 2,
    RIGHT = 4,
    DOWN = 8,
    LEFT = 16,
    SHOOT = 32
};

enum Events {
    SHOT = 64,
    QUIT = 128
};

enum ObjectType {
    UNDEFINED = 0,
    PLAYER = 256,
    ENEMY = 512,
    BULLET = 1024,
    POWER_UP = 2048,
    EXPLOSION = 4096
};

enum ExplosionType {
    SMALL = 8192,
    MEDIUM = 16384,
    BIG = 32768
};