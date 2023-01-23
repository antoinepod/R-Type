/*
** EPITECH PROJECT, 2022
** sound.hpp
** File description:
** sound
*/

#include "raylib.h"

namespace rtype {
    class MySound {
    private:
    public:
        MySound() = default;
        virtual ~MySound() = delete;

        // Load sound from file
        static Sound loadSound(const char *fileName);

        // Unload sound
        static void unloadSound(Sound sound);

        // Play a sound
        static void playSound(Sound sound);

        // Stop playing a sound
        static void stopSound(Sound sound);

        // Check if a sound is currently playing
        static bool isSoundPlaying(Sound sound);

        // Set volume for a sound (1.0 is max level)
        static void setSoundVolume(Sound sound, float volume);

        // Initialize audio device and context
        static void initAudioDevice(void);

        // Close the audio device and context
        static void closeAudioDevice(void);
    };
}