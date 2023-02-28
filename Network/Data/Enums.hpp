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
    SIMPLE_SHOOT = 32,
    LASER_SHOOT = 64,
    ROCKET_SHOOT = 128,
    LEVEL1 = 256,
    LEVEL2 = 512,
    LEVEL3 = 1024,
    LEVEL4 = 2048,
    LEVEL5 = 4096,
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
    SOUND = 64,
    GAME_STATE = 128
};

enum ExplosionType {
    MISSILE = 2,
    SMALL = 4,
    MEDIUM = 8,
    BIG = 16
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
    EXPLOSION_MISSILE = 16,
    EXPLOSION_SMALL = 32,
    EXPLOSION_MEDIUM = 64,
    EXPLOSION_BIG = 128
};

enum MusicType {
    MENU_MUSIC = 2,
    GAME_MUSIC = 4
};

enum GameState {
    WAITING = 2,
    LEVEL_1 = 4,
    LEVEL_2 = 8,
    LEVEL_3 = 16,
    LEVEL_4 = 32,
    LEVEL_5 = 64,
    WIN = 128,
    LOOSE = 256
};