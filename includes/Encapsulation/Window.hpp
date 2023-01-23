/*
** EPITECH PROJECT, 2022
** window.cpp
** File description:
** window
*/

#pragma once

#include <iostream>
#include "raylib.h"

namespace rtype {
    class Window {
    private:
        const std::string title;

    public:
        // Initialize window and OpenGL context
        Window() = delete;

        // Close window and unload OpenGL context
        virtual ~Window() = delete;

        // Initialize window and OpenGL context
        static void initWindow(int width, int height, const char *title);

        // Close window and unload OpenGL context
        static void closeWindow(void);

        // Check if KEY_ESCAPE pressed or Close icon pressed
        static bool shouldClose(void);

        // Check if window has been initialized successfully
        static bool isReady(void);

        // Check if window is currently fullscreen
        static bool isFullscreen(void);

        // Check if window is currently hidden (only PLATFORM_DESKTOP)
        static bool isHidden(void);

        // Check if window is currently minimized (only PLATFORM_DESKTOP)
        static bool isMinimized(void);

        // Check if window is currently maximized (only PLATFORM_DESKTOP)
        static bool isMaximized(void);

        // Check if window is currently focused (only PLATFORM_DESKTOP)
        static bool isFocused(void);

        // Check if window has been resized last frame
        static bool isResized(void);

        // Check if one specific window flag is enabled
        static bool isState(const unsigned int &flag);

        // Set window configuration state using flags
        static void setState(const unsigned int &flags);

        // Clear window configuration state flags
        static void clearState(const unsigned int &flags);

        // Toggle window state: fullscreen/windowed (only PLATFORM_DESKTOP)
        static void toggleFullscreen(void);

        // Set window state: maximized, if resizable (only PLATFORM_DESKTOP)
        static void maximize(void);

        // Set window state: minimized, if resizable (only PLATFORM_DESKTOP)
        static void minimize(void);

        // Set window state: not minimized/maximized (only PLATFORM_DESKTOP)
        static void restore(void);

        // Set icon for window (only PLATFORM_DESKTOP)
        static void setIcon(const Image &image);

        // Set title for window (only PLATFORM_DESKTOP)
        static void setTitle(const std::string &title);

        // Set window position on screen (only PLATFORM_DESKTOP)
        static void setPosition(const int &x, const int &y);

        // Set monitor for the current window (fullscreen mode)
        static void setMonitor(const int &monitor);

        // Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)
        static void setMinSize(const int &width, const int &height);

        // Set window dimensions
        static void setSize(const int &width, const int &height);

        // Get native window handle
        static void *getHandle(void);

        // Get current screen width
        static int getScreenWidth(void);

        // Get current screen height
        static int getScreenHeight(void);

        // Get number of connected monitors
        static int getMonitorCount(void);

        // Get current connected monitor
        static int getCurrentMonitor(void);

        // Get specified monitor position
        static Vector2 getMonitorPosition(const int &monitor);

        // Get specified monitor width (max available by monitor)
        static int getMonitorWidth(const int &monitor);

        // Get specified monitor height (max available by monitor)
        static int getMonitorHeight(const int &monitor);

        // Get specified monitor physical width in millimetres
        static int getMonitorPhysicalWidth(const int &monitor);

        // Get specified monitor physical height in millimetres
        static int getMonitorPhysicalHeight(const int &monitor);

        // Get specified monitor refresh rate
        static int getMonitorRefreshRate(const int &monitor);

        // Get window position XY on monitor
        static Vector2 getPosition(void);

        // Get window scale DPI factor
        static Vector2 getScaleDPI(void);

        // Get the human-readable, UTF-8 encoded name of the primary monitor
        static const std::string getMonitorName(const int &monitor);

        // Set clipboard text content
        static void setClipboardText(const std::string &text);

        // Get clipboard text content
        static const char *getClipboardText(void);

        // Set target FPS (maximum)
        static void setTargetFPS(int fps);

        // Setup init configuration flags (view FLAGS)
        static void setConfigFlags(unsigned int flags);

        // Set mouse cursor
        static void setMouseCursor(int cursor);
    };
}