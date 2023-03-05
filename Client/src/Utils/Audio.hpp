/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-william.mallevays
** File description:
** Audio.hpp
*/

#pragma once

#include "Data/Enums.hpp"
#include <SFML/Audio.hpp>


class Audio {
public:
    Audio();
    ~Audio();

    // Musics
    void PlayMusic(MusicType musicType);
    void StopMusic(MusicType musicType);

    // Sounds
    void PlaySound(SoundType soundType);

private:
    // Musics
    std::map<MusicType, std::shared_ptr<sf::Music>> _music;

    // Sounds
    std::map<SoundType, sf::Sound> _sound;
    std::map<SoundType, std::shared_ptr<sf::SoundBuffer>> _soundBuffer;
};