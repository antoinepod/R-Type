/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-william.mallevays
** File description:
** R-Type.cpp
*/

#include "R-Type.hpp"


RType::RType() {
    srand((int)time(0));

    _arcadeFont.loadFromFile("assets/Fonts/PublicPixel.ttf");
    _window = std::make_shared<sf::RenderWindow>(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "R-Type");
    _window->setFramerateLimit(60);

    _backgroundTexture.loadFromFile("assets/Images/SpaceBackground.png");
    _backgroundPosition = {0, 0};
    _background.setTexture(_backgroundTexture);
    _background.setPosition(_backgroundPosition);

    for (int i = 0; i < 5; i++) {
        _planetTextures.push_back(std::make_shared<sf::Texture>());
        _planetTextures[i]->loadFromFile("assets/Images/Planets/Planet" + std::to_string(i + 1) + ".png");
        _planetPositions.emplace_back(float(rand() % (SCREEN_WIDTH * 2)), float(rand() % (SCREEN_HEIGHT - 200)) + 100);
        _planets.emplace_back();
        _planets[i].setTexture(*_planetTextures[i]);
        _planets[i].setPosition(_planetPositions[i]);
        _planets[i].setScale(3, 3);
    }

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
        DrawBackground();
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

void RType::DrawBackground() {
    _backgroundPosition.x -= 1;
    _background.setPosition(_backgroundPosition);
    _window->draw(_background);
    if (_backgroundPosition.x < -SCREEN_WIDTH)
        _backgroundPosition.x = 0;

    for (int i = 0; i < 5; i++) {
        _planetPositions[i].x -= (i + 1) * 1.1;
        _planets[i].setPosition(_planetPositions[i]);
        _window->draw(_planets[i]);
        if (_planetPositions[i].x < -250)
            _planetPositions[i].x = SCREEN_WIDTH * 2 + 100;
    }
}
