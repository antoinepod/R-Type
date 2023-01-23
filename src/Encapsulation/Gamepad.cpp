/*
** EPITECH PROJECT, 2022
** gamepad.cpp
** File description:
** gamepad
*/

#include "MyGamepad.hpp"

namespace rtype {
    bool MyGamepad::isKeyPressed(int key) {
        return IsKeyPressed(key);
    }

    bool MyGamepad::isKeyDown(int key) {
        return IsKeyDown(key);
    }

    bool MyGamepad::isGamepadAvailable(int gamepad) {
        return IsGamepadAvailable(gamepad);
    }

    bool MyGamepad::isGamepadButtonDown(int gamepad, int button) {
        return IsGamepadButtonDown(gamepad, button);
    }

    float MyGamepad::getGamepadAxisMovement(int gamepad, int axis) {
        return GetGamepadAxisMovement(gamepad, axis);
    }

    bool MyGamepad::isGamepadButtonPressed(int gamepad, int button) {
        return IsGamepadButtonPressed(gamepad, button);
    }

    bool MyGamepad::isMouseButtonPressed(int button) {
        return IsMouseButtonPressed(button);
    }

    // Get mouse position XY
    Vector2 MyGamepad::getMousePosition(void) {
        return GetMousePosition();
    }
}