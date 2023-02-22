/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-william.mallevays
** File description:
** R-Type.cpp
*/

#include "R-Type.hpp"


RType::RType() {
    _arcadeFont.loadFromFile("assets/Fonts/PublicPixel.ttf");
    _window = std::make_shared<sf::RenderWindow>(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "R-Type");
    _window->setFramerateLimit(60);

    _gameStatus[GameStatus::MENU] = std::make_shared<Menu>();
    _gameStatus[GameStatus::GAME] = std::make_shared<Game>();
    _gameStatus[GameStatus::SETTINGS] = std::make_shared<Settings>();
    _currentGameStatus = GameStatus::MENU;

    _fpsText = sf::Text("", _arcadeFont, 20);
    _fpsText.setPosition(10, 10);
    _fpsText.setFillColor(sf::Color::Green);

    // Debug
    _serverIp = "localhost";
}

RType::~RType() {
    _window->close();
}

void RType::Start() {
    Inputs inputs;
    while (_window->isOpen())
    {
        sf::Event event{};
        if (_window->pollEvent(event) && event.type == sf::Event::Closed) {
            _window->close();
            exit(0);
        }
        _currentGameStatus = _gameStatus[_currentGameStatus]->ManageInput(event, _serverIp, inputs);

        if (_currentGameStatus == GameStatus::CLOSE)
            break;

        _window->clear(sf::Color::Black);
        _gameStatus[_currentGameStatus]->Display(_window);
        DrawFps();
        _window->display();
    }
    _gameStatus[GameStatus::GAME].reset();
    std::this_thread::sleep_for(std::chrono::milliseconds(16));
}

void RType::DrawFps() {
    _currentTime = _clock.restart().asSeconds();
    _fps = 1.0f / _currentTime;

    _fpsText.setString(std::to_string(int(_fps)));

    _window->draw(_fpsText);
}
