/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Music
*/

#ifndef MUSIC_HPP_
#define MUSIC_HPP_

#include <SFML/Audio.hpp>

class Music
{
    public:
        sf::Music music;
        sf::Sound sound;
        sf::SoundBuffer buffer;

        int newMusic(const char *);
        void playMusic();
        void stopMusic();
        int newSound(const char *);
        void playSound();
        void stopSound();
};

#endif /* !MUSIC_HPP_ */
