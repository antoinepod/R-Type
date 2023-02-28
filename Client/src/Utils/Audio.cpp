/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-william.mallevays
** File description:
** Audio.cpp
*/

#include "Audio.hpp"

Audio::Audio() {
    // Musics
    _music[MusicType::MENU_MUSIC] = std::make_shared<sf::Music>();
    _music[MusicType::MENU_MUSIC]->openFromFile("assets/Sounds/MenuMusic.ogg");
    _music[MusicType::MENU_MUSIC]->setLoop(true);
    _music[MusicType::GAME_MUSIC] = std::make_shared<sf::Music>();
    _music[MusicType::GAME_MUSIC]->openFromFile("assets/Sounds/GameMusic.ogg");
    _music[MusicType::GAME_MUSIC]->setLoop(true);

    // Bullet Sounds
    for (int i = 1; i <= 3; i++) {
        _soundBuffer[(SoundType)(pow(SoundType::SHOOT_SIMPLE, i))] = std::make_shared<sf::SoundBuffer>();
        _soundBuffer[(SoundType)(pow(SoundType::SHOOT_SIMPLE, i))]->loadFromFile("assets/Sounds/Bullet" + std::to_string(i) + ".wav");
        _sound[(SoundType)(pow(SoundType::SHOOT_SIMPLE, i))].setBuffer(*_soundBuffer[(SoundType)(pow(SoundType::SHOOT_SIMPLE, i))]);
    }
    _sound[SoundType::SHOOT_LASER].setVolume(150);
    _sound[SoundType::SHOOT_ROCKET].setVolume(200);

    // Explosion Sounds
    for (int i = 1; i <= 4; i++) {
        _soundBuffer[(SoundType)(8 * pow(2, i))] = std::make_shared<sf::SoundBuffer>();
        _soundBuffer[(SoundType)(8 * pow(2, i))]->loadFromFile("assets/Sounds/Explosion" + std::to_string(i) + ".wav");
        _sound[(SoundType)(8 * pow(2, i))].setBuffer(*_soundBuffer[(SoundType)(8 * pow(2, i))]);
    }
}

Audio::~Audio() {
    // Musics
    for (auto &music : _music) {
        if (music.second->getStatus() == sf::SoundSource::Status::Playing)
            music.second->stop();
        music.second.reset();
    }

    // Sounds
    for (auto &sound : _sound)
        sound.second.resetBuffer();

    // Sound Buffers
    for (auto &sound : _soundBuffer)
        sound.second.reset();
}

// Musics
void Audio::PlayMusic(MusicType musicType) {
    if (_music[musicType]->getStatus() != sf::SoundSource::Status::Playing)
        _music[musicType]->play();
}

void Audio::StopMusic(MusicType musicType) {
    if (_music[musicType]->getStatus() == sf::SoundSource::Status::Playing)
        _music[musicType]->stop();
}

// Sounds
void Audio::PlaySound(SoundType soundType) {
    _sound[soundType].play();
}
