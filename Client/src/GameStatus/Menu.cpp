/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-william.mallevays
** File description:
** Menu.cpp
*/

#include "Menu.hpp"

Menu::Menu() {
    _menuMusic.openFromFile("assets/Sounds/MenuMusic.ogg");
    _menuMusic.setLoop(true);
    _arcadeFont.loadFromFile("assets/Fonts/PublicPixel.ttf");
    _title = sf::Text("R-Type", _arcadeFont, 80);
    _title.setPosition(750 - (_title.getLocalBounds().width / 2), 200);
    _title.setFillColor(sf::Color::White);

    _serverIpInfo = sf::Text("", _arcadeFont, 20);
    _serverIpInfo.setFillColor(sf::Color(128,128,128,255));

    std::vector<std::string> buttonNames = {"Play", "Settings", "Quit"};
    for (int i = 0; i < buttonNames.size(); i++) {
        _buttons.emplace_back(buttonNames[i], _arcadeFont, 40);
        _buttons[i].setPosition(750 - (_buttons[i].getLocalBounds().width / 2), (float)(450 + (i * 100)));
    }

    _selectedButton = 0;
    _serverIp = "";
}

Menu::~Menu() {
    if (_menuMusic.getStatus() == sf::Music::Playing)
        _menuMusic.stop();
};

GameStatus Menu::ManageInput(sf::Event event, std::string &serverIp, Inputs &inputs) {
    _serverIp = serverIp;

    if (_menuMusic.getStatus() != sf::Music::Playing)
        _menuMusic.play();

    // Handle keyboard
    if (event.type == sf::Event::KeyPressed) {
        if (inputs.GetUp() && _selectedButton > 0)
            _selectedButton--;
        if (inputs.GetDown() && _selectedButton < _buttons.size() - 1)
            _selectedButton++;
        if (event.key.code == sf::Keyboard::Enter)
            return GetSelectedButton();
    }

    // Handle joystick
    if (event.type == sf::Event::JoystickMoved) {
        if (event.joystickMove.position == -100 && _selectedButton > 0)
            _selectedButton--;
        if (event.joystickMove.position == 100 && _selectedButton < _buttons.size() - 1)
            _selectedButton++;
    } if (event.type == sf::Event::JoystickButtonPressed && sf::Joystick::isButtonPressed(0, 0))
            return GetSelectedButton();

    if (event.type == sf::Event::JoystickConnected) {
        std::cout << "Joystick connected" << std::endl;
    }

    if (event.type == sf::Event::JoystickMoved) {
        std::cout << "Joystick moved" << std::endl;
        std::cout << "Joystick ID: " << event.joystickMove.joystickId << std::endl;
        std::cout << "Axis: " << event.joystickMove.axis << std::endl;
        std::cout << "Position: " << event.joystickMove.position << std::endl;
    }

    return GameStatus::MENU;
}

void Menu::Display(const std::shared_ptr<sf::RenderWindow>& window){
    window->draw(_title);

    for (int i = 0; i < _buttons.size(); i++) {
        if (i == _selectedButton)
            _buttons[i].setFillColor(sf::Color::Blue);
        else
            _buttons[i].setFillColor(sf::Color::White);
        window->draw(_buttons[i]);
    }

    if (_selectedButton == 0) {
        if (_serverIp.empty()) {
            _serverIpInfo.setString("Server IP not set, please go to Settings.");
            _serverIpInfo.setPosition(750 - (_serverIpInfo.getLocalBounds().width / 2), 500);
        } else {
            _serverIpInfo.setString(_serverIp);
            _serverIpInfo.setPosition(750 - (_serverIpInfo.getLocalBounds().width / 2), 500);
        }
        window->draw(_serverIpInfo);
    }
}

GameStatus Menu::GetSelectedButton() {
    switch (_selectedButton) {
        case 0:
            if (_serverIp.empty())
                break;
            else {
                _menuMusic.stop();
                return GameStatus::GAME;
            }
        case 1:
            return GameStatus::SETTINGS;
        case 2:
            return GameStatus::CLOSE;
        default:
            return GameStatus::MENU;
    }
    return GameStatus::MENU;
}
