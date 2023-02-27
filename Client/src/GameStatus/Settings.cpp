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

    _texts.emplace_back("Server IP address:  ", _arcadeFont, 40);
    _texts[0].setPosition(50, 300);
    _texts[0].setFillColor(sf::Color::White);

    _texts.emplace_back("Volume:  50%", _arcadeFont, 40);
    _texts[1].setPosition(50, 500);
    _texts[1].setFillColor(sf::Color::White);

    _selectedText = 0;
}

Settings::~Settings() = default;

GameStatus Settings::ManageInput(sf::Event event, std::string &serverIp, Inputs &inputs) {
    _texts[0].setString("Server IP address:  " + serverIp);

    // Handle keyboard
    if (_selectedText == 0 && event.type == sf::Event::TextEntered && std::isprint((char)event.text.unicode))
        serverIp.push_back((char)event.text.unicode);

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape)
            return GameStatus::MENU;
        if (_selectedText == 0 && event.key.code == sf::Keyboard::BackSpace && !serverIp.empty())
            serverIp.pop_back();

        if (inputs.GetUp() && _selectedText > 0)
            _selectedText--;
        else if (inputs.GetDown() && _selectedText < _texts.size() - 1)
            _selectedText++;
        else if (inputs.GetLeft() && _selectedText == 1 && sf::Listener::getGlobalVolume() >= 10)
            sf::Listener::setGlobalVolume(sf::Listener::getGlobalVolume() - 10);
        else if (inputs.GetRight() && _selectedText == 1 && sf::Listener::getGlobalVolume() <= 90)
            sf::Listener::setGlobalVolume(sf::Listener::getGlobalVolume() + 10);
    }

    // Handle joystick
    if (event.type == sf::Event::JoystickButtonPressed && sf::Joystick::isButtonPressed(0, 1))
            return GameStatus::MENU;

    float PovX = sf::Joystick::getAxisPosition(0, sf::Joystick::PovX);
    float PovY = sf::Joystick::getAxisPosition(0, sf::Joystick::PovY);
    float AxisX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
    float AxisY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
    if (((PovX == 0 && PovY == -100) || (AxisX > -100 && AxisX < 100 && AxisY < 0)) && _selectedText > 0)
        _selectedText--;
    if (((PovX == 0 && PovY == 100) || (AxisX > -100 && AxisX < 100 && AxisY > 0)) && _selectedText < _texts.size() - 1)
        _selectedText++;
    if (((PovX == -100 && PovY == 0) || (AxisX < 0 && AxisY > -100 && AxisY < 100)) && _selectedText == 1 && sf::Listener::getGlobalVolume() >= 10)
        sf::Listener::setGlobalVolume(sf::Listener::getGlobalVolume() - 10);
    if (((PovX == 100 && PovY == 0) || (AxisX > 0 && AxisY > -100 && AxisY < 100)) && _selectedText == 1 && sf::Listener::getGlobalVolume() <= 90)
        sf::Listener::setGlobalVolume(sf::Listener::getGlobalVolume() + 10);

    _texts[1].setString("Volume:  " + std::to_string(int(sf::Listener::getGlobalVolume())) + "%");

    return GameStatus::SETTINGS;
}

void Settings::Display(const std::shared_ptr<sf::RenderWindow>& window, const std::shared_ptr<Audio>& audio) {
    window->draw(_title);

    for (int i = 0; i < _texts.size(); i++) {
        if (_selectedText == i) {
            _texts[i].setFillColor(sf::Color::Blue);
        } else {
            _texts[i].setFillColor(sf::Color::White);
        }
        window->draw(_texts[i]);
    }
}
