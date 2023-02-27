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
    PLAYER = 2,
    ENEMY = 4,
    BULLET = 8,
    POWER_UP = 16,
    EXPLOSION = 32,
    SOUND = 64
};

enum ExplosionType {
    SMALL = 2,
    MEDIUM = 4,
    BIG = 8
};

enum BulletType {
    SIMPLE = 2,
    LASER = 4,
    ROCKET = 8
};

enum SoundType {
    SHOOT_SIMPLE = 2,
    SHOOT_LASER = 4,
    SHOOT_ROCKET = 8,
    EXPLOSION_SMALL = 16,
    EXPLOSION_MEDIUM = 32,
    EXPLOSION_BIG = 64
};

enum MusicType {
    MENU_MUSIC = 2,
    GAME_MUSIC = 4
};