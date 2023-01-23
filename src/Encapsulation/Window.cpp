/*
** EPITECH PROJECT, 2022
** window.cpp
** File description:
** window
*/

#include "Window.hpp"

namespace rtype {
    void Window::initWindow(int width, int height, const char *title) {
        return InitWindow(width, height, title);
    }

    void Window::closeWindow(void) {
        return CloseWindow();
    }                                                 // Close window and unload OpenGL context

    bool Window::shouldClose(void) {
        return WindowShouldClose();
    }
    
    bool Window::isReady(void) {
        return IsWindowReady();
    }

    bool Window::isFullscreen(void) {
        return IsWindowFullscreen();
    }
    
    bool Window::isHidden(void) {
        return IsWindowHidden();
    }
    
    bool Window::isMinimized(void) {
        return IsWindowMinimized();
    }
    
    bool Window::isMaximized(void) {
        return IsWindowMaximized();
    }
    
    bool Window::isFocused(void) {
        return IsWindowFocused();
    }
    
    bool Window::isResized(void) {
        return IsWindowResized();
    }
    
    bool Window::isState(const unsigned int &flag) {
        return IsWindowState(flag);
    }
    
    void Window::setState(const unsigned int &flags) {
        return SetWindowState(flags);
    }
    
    void Window::clearState(const unsigned int &flags) {
        return ClearWindowState(flags);
    }
    
    void Window::toggleFullscreen(void) {
        return ToggleFullscreen();
    }
    
    void Window::maximize(void) {
        return MaximizeWindow();
    }
    
    void Window::minimize(void) {
        return MinimizeWindow();
    }
    
    void Window::restore(void) {
        return RestoreWindow();
    }
    
    void Window::setIcon(const Image &image) {
        return SetWindowIcon(image);
    }
    
    void Window::setTitle(const std::string &title) {
        return SetWindowTitle(title.c_str());
    }
    
    void Window::setPosition(const int &x, const int &y) {
        return SetWindowPosition(x, y);
    }
    
    void Window::setMonitor(const int &monitor) {
        return SetWindowMonitor(monitor);
    }
    
    void Window::setMinSize(const int &width, const int &height) {
        return SetWindowMinSize(width, height);
    }
    
    void Window::setSize(const int &width, const int &height) {
        return SetWindowSize(width, height);
    }
    
    void *Window::getHandle(void) {
        return GetWindowHandle();
    }
    
    int Window::getScreenWidth(void) {
        return GetScreenWidth();
    }
    
    int Window::getScreenHeight(void) {
        return GetScreenHeight();
    }
    
    int Window::getMonitorCount(void) {
        return GetMonitorCount();
    }
    
    int Window::getCurrentMonitor(void) {
        return GetCurrentMonitor();
    }
    
    Vector2 Window::getMonitorPosition(const int &monitor) {
        return GetMonitorPosition(monitor);
    }
    
    int Window::getMonitorWidth(const int &monitor) {
        return GetMonitorWidth(monitor);
    }
    
    int Window::getMonitorHeight(const int &monitor) {
        return GetMonitorHeight(monitor);
    }
    
    int Window::getMonitorPhysicalWidth(const int &monitor) {
        return GetMonitorPhysicalWidth(monitor);
    }
    
    int Window::getMonitorPhysicalHeight(const int &monitor) {
        return GetMonitorPhysicalHeight(monitor);
    }
    
    int Window::getMonitorRefreshRate(const int &monitor) {
        return GetMonitorRefreshRate(monitor);
    }
    
    Vector2 Window::getPosition(void) {
        return GetWindowPosition();
    }
    
    Vector2 Window::getScaleDPI(void) {
        return GetWindowScaleDPI();
    }
    
    const std::string Window::getMonitorName(const int &monitor) {
        const std::string monitorName(GetMonitorName(monitor));
        return monitorName;
    }
    
    void Window::setClipboardText(const std::string &text) {
        return SetClipboardText(text.c_str());
    }
    
    const char *Window::getClipboardText(void) {
        return GetClipboardText();
    }

    void Window::setTargetFPS(int fps) {
        return SetTargetFPS(fps);
    }

    void Window::setConfigFlags(unsigned int flags) {
        return SetConfigFlags(flags);
    }

    void Window::setMouseCursor(int cursor) {
        return SetMouseCursor(cursor);
    }
}
