/*
** EPITECH PROJECT, 2023
** window.cpp
** File description:
** window
*/

#include "../../includes/Encapsulation/Window.hpp"

namespace rtype {
    void Window::initWindow(int width, int height, const char *title) {
        return InitWindow(width, height, title);
    }

    void Window::closeWindow(void) {
        return CloseWindow();
    }
}