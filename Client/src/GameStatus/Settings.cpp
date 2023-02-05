/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-william.mallevays
** File description:
** Settings.cpp
*/

#include "Settings.hpp"


Settings::Settings() {
    _arcadeFont.loadFromFile("assets/Fonts/PublicPixel.ttf");
    _title = sf::Text("Settings", _arcadeFont, 60);
    _title.setPosition(750 - (_title.getLocalBounds().width / 2), 50);
    _title.setFillColor(sf::Color::White);

    _ipText = sf::Text("Server IP address :", _arcadeFont, 40);
    _ipText.setPosition(50, 200);
    _ipText.setFillColor(sf::Color::White);

    _ipNumber = sf::Text("", _arcadeFont, 40);
    _ipNumber.setPosition(900, 200);
    _ipNumber.setFillColor(sf::Color::White);
}

Settings::~Settings() {
}

void Settings::Display(const std::shared_ptr<sf::RenderWindow>& window) {
    window->draw(_title);

    window->draw(_ipText);
    window->draw(_ipNumber);
}

GameStatus Settings::ManageInput(sf::Event event, std::string &serverIp) {
    _ipNumber.setString(serverIp);

    if (event.type == sf::Event::TextEntered && std::isprint((char)event.text.unicode))
        serverIp.push_back((char)event.text.unicode);

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape)
            return GameStatus::MENU;
        if (event.key.code == sf::Keyboard::BackSpace && !serverIp.empty())
            serverIp.pop_back();
    }

    return GameStatus::SETTINGS;
}
