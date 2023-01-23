/*
** EPITECH PROJECT, 2022
** color.hpp
** File description:
** color
*/

#pragma once

#include "raylib.h"

struct MyColor : Color {
    using uchar = unsigned char;
    constexpr MyColor() : Color{0, 0, 0, 0} {}
    constexpr MyColor(uchar r, uchar g, uchar b, uchar a) : Color{r, g, b, a}{}
    constexpr MyColor(Color color) : Color(color) {}
};

namespace rtype {
    #undef LIGHTGRAY
    #undef GRAY       
    #undef DARKGRAY 
    #undef YELLOW 
    #undef GOLD       
    #undef ORANGE
    #undef PINK       
    #undef RED
    #undef MAROON
    #undef GREEN
    #undef LIME       
    #undef DARKGREEN
    #undef SKYBLUE
    #undef BLUE       
    #undef DARKBLUE
    #undef PURPLE
    #undef VIOLET
    #undef DARKPURPLE
    #undef BEIGE
    #undef BROWN
    #undef DARKBROWN
    #undef WHITE
    #undef BLACK
    #undef BLANK 
    #undef MAGENTA
    #undef RAYWHITE

    constexpr MyColor LIGHTGRAY(200, 200, 200, 255);
    constexpr MyColor GRAY(130, 130, 130, 255);
    constexpr MyColor DARKGRAY(80, 80, 80, 255);
    constexpr MyColor YELLOW(253, 249, 0, 255);
    constexpr MyColor GOLD(255, 203, 0, 255);
    constexpr MyColor ORANGE(255, 161, 0, 255);
    constexpr MyColor PINK(255, 109, 194, 255);
    constexpr MyColor RED(230, 41, 55, 255);
    constexpr MyColor MAROON(190, 33, 55, 255);
    constexpr MyColor GREEN(0, 228, 48, 255);
    constexpr MyColor LIME(0, 158, 47, 255);
    constexpr MyColor DARKGREEN(0, 117, 44, 255);
    constexpr MyColor SKYBLUE(102, 191, 255, 255);
    constexpr MyColor BLUE(0, 121, 241, 255);
    constexpr MyColor DARKBLUE(0, 82, 172, 255);
    constexpr MyColor PURPLE(200, 122, 255, 255);
    constexpr MyColor VIOLET(135, 60, 190, 255);
    constexpr MyColor DARKPURPLE(112, 31, 126, 255);
    constexpr MyColor BEIGE(211, 176, 131, 255);
    constexpr MyColor BROWN(127, 106, 79, 255);
    constexpr MyColor DARKBROWN(76, 63, 47, 255);
    constexpr MyColor WHITE(255, 255, 255, 255);
    constexpr MyColor BLACK(0, 0, 0, 255);
    constexpr MyColor BLANK(0, 0, 0, 0);
    constexpr MyColor MAGENTA(255, 0, 255, 255);
    constexpr MyColor RAYWHITE(245, 245, 245, 255);
}
