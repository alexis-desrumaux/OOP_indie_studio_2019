/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Music
*/

#include <iostream>
#include <fstream>
#include "include.hpp"

using namespace irr;
using namespace video;
using namespace scene;
using namespace core;
using namespace gui;

int Music::newMusic(const char *path)
{
    if (!this->music.openFromFile(path)) {
        std::cerr << "Error while loading " << path << std::endl;
        return -1;
    }
    std::cout << "Music loaded successfully!" << std::endl;
    return 0;
}

void Music::stopMusic()
{
    this->music.stop();
}

void Music::playMusic()
{
    this->music.play();
}

int Music::newSound(const char *path)
{
    if (!this->buffer.loadFromFile(path)) {
        std::cerr << "Error while loading " << path << std::endl;
        return -1;
    }
    this->sound.setBuffer(this->buffer);
    std::cout << "Sound loaded successfully!" << std::endl;
    return 0;
}

void Music::playSound()
{
    // if (this->sound.getStatus() != sf::Sound::Playing) {
    //     this->sound.play();
    // }
    sf::Sound sound;

    sound.setBuffer(this->buffer);
    std::cout << "Playing sound!" << std::endl;
    sound.play();
}

void Music::stopSound()
{
    // this->sound.stop();
    sf::Sound sound;

    sound.setBuffer(this->buffer);
    sound.stop();
}
