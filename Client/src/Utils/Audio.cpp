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

    // Sounds
    _soundBuffer[SoundType::SHOOT_SIMPLE] = std::make_shared<sf::SoundBuffer>();
    _soundBuffer[SoundType::SHOOT_SIMPLE]->loadFromFile("assets/Sounds/simpleBullet.wav");
    _sound[SoundType::SHOOT_SIMPLE].setBuffer(*_soundBuffer[SoundType::SHOOT_SIMPLE]);
}

Audio::~Audio() {
    // Musics
    for (auto &music : _music) {
        if (music.second->getStatus() == sf::SoundSource::Status::Playing)
            music.second->stop();
        music.second.reset();
    }

    // Sounds
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
