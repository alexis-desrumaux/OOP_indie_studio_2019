/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Game
*/

#include "Bomberman.hpp"

int Game::update(MyEventReceiver *event)
{
    this->videoDriver->beginScene(true, true, SColor(255, 71, 101, 249));

    for (size_t i = 0; i != this->gameObj->_player.size(); i += 1)
        this->gameObj->_player.at(i)->compute(event);
    for (size_t i = 0; i != this->gameObj->_ia.size(); i += 1)
        this->gameObj->_ia.at(i)->compute();
    this->gameObj->_camera->compute(event);

    this->sceneManager->drawAll();

    this->videoDriver->endScene();
    return 0;
}

Game::Game(IrrlichtDevice *device, configBomberman_t *cf, int selected_map)
{
    this->gameObj = new GameObject(device, cf);
    this->gameObj->createPool();
    this->gameObj->init(selected_map);
    this->config = cf;
    this->device = device;
    this->videoDriver = this->device->getVideoDriver();
    this->sceneManager = this->device->getSceneManager();
    this->gui = this->device->getGUIEnvironment();
}

Game::~Game()
{
    if (this->gameObj != NULL) {
        delete this->gameObj;
    }
}
