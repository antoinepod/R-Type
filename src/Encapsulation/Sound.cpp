/*
** EPITECH PROJECT, 2022
** sound.cpp
** File description:
** sound
*/

#include "Sound.hpp"

namespace rtype {
    Sound MySound::loadSound(const char *fileName) {
        return LoadSound(fileName);
    }

    void MySound::unloadSound(Sound sound) {
        return UnloadSound(sound);
    }

    void MySound::playSound(Sound sound) {
        return PlaySound(sound);
    }

    void MySound::stopSound(Sound sound) {
        return StopSound(sound);
    }

    bool MySound::isSoundPlaying(Sound sound) {
        return IsSoundPlaying(sound);
    }

    void MySound::setSoundVolume(Sound sound, float volume) {
        return SetSoundVolume(sound, volume);
    }
    void MySound::initAudioDevice(void) {
        return InitAudioDevice();
    }

    void MySound::closeAudioDevice(void) {
        CloseAudioDevice();
    }
}