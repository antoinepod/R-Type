/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** enums.hpp
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

namespace RType {

    enum Actions {
        UP = 2,
        RIGHT = 4,
        DOWN = 8,
        LEFT = 16,
        EVENT = 32
    };

    enum Events {
        SHOT = 64,
        QUIT = 128
    };

}