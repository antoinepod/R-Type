/*
** EPITECH PROJECT, 2023
** window.hpp
** File description:
** window
*/

#pragma once

#include <iostream>
#include "raylib.h"

namespace rtype {
    class Window {
    public:
        static void initWindow(int width, int height, const char *title);

        static void closeWindow(void);
    };
}
