/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameObjects
*/

#include "Bomberman.hpp"

std::vector<KeyLayout> createKeyLayout()
{
    std::vector<KeyLayout> k;

    k.push_back({irr::KEY_UP, irr::KEY_DOWN, irr::KEY_LEFT, irr::KEY_RIGHT, irr::KEY_RETURN});
    k.push_back({irr::KEY_KEY_Z, irr::KEY_KEY_S, irr::KEY_KEY_Q, irr::KEY_KEY_D, irr::KEY_KEY_X});
    k.push_back({irr::KEY_KEY_U, irr::KEY_KEY_J, irr::KEY_KEY_H, irr::KEY_KEY_K, irr::KEY_KEY_N});
    k.push_back({irr::KEY_KEY_F, irr::KEY_KEY_V, irr::KEY_KEY_C, irr::KEY_KEY_B, irr::KEY_KEY_G});
    return k;
}

void GameObject::createBombermanWithType()
{
    if (this->_configBbmCharacter->BombermanOne == ObjType::Bomberman) {
        this->_player.push_back(new Bomberman());
    }
    else if (this->_configBbmCharacter->BombermanOne == ObjType::BombermanIA) {
        this->_ia.push_back(new BombermanIA());
    }
    if (this->_configBbmCharacter->BombermanTwo == ObjType::Bomberman) {
        this->_player.push_back(new Bomberman());
    }
    else if (this->_configBbmCharacter->BombermanTwo == ObjType::BombermanIA) {
        this->_ia.push_back(new BombermanIA());
    }
}

void GameObject::initBombermanWithType()
{
    std::vector<KeyLayout> myKL = createKeyLayout();

    if (this->_player.size() == 2) {
        this->_player.at(0)->init(this->_configBbmCharacter->BombermanOneName, this->_map->getSpawnPoint(0), myKL.at(0));
        this->_player.at(1)->init(this->_configBbmCharacter->BombermanTwoName, this->_map->getSpawnPoint(1), myKL.at(1));
    }
    else if (this->_ia.size() == 2) {
        this->_ia.at(0)->init(this->_configBbmCharacter->BombermanOneName, this->_map->getSpawnPoint(0));
        this->_ia.at(1)->init(this->_configBbmCharacter->BombermanTwoName, this->_map->getSpawnPoint(1));
    }
    else if (this->_player.size() == 1 && this->_ia.size() == 1) {
        if (this->_configBbmCharacter->BombermanOne == ObjType::Bomberman) {
            this->_player.at(0)->init(this->_configBbmCharacter->BombermanOneName, this->_map->getSpawnPoint(0), myKL.at(0));
            this->_ia.at(0)->init(this->_configBbmCharacter->BombermanTwoName, this->_map->getSpawnPoint(1));
        }
        else if (this->_configBbmCharacter->BombermanOne == ObjType::BombermanIA) {
            this->_ia.at(0)->init(this->_configBbmCharacter->BombermanOneName, this->_map->getSpawnPoint(0));
            this->_player.at(0)->init(this->_configBbmCharacter->BombermanTwoName, this->_map->getSpawnPoint(1), myKL.at(0));
        }
    }
}

void GameObject::init(int selected_map)
{
    if (selected_map == 1)
        this->_map->init("./map/1m");
    else if (selected_map == 2)
        this->_map->init("./map/1m2");
    else if (selected_map == 3)
        this->_map->init("./map/test");
    initBombermanWithType();
    this->_camera->init(this->_map->getCameraPosition(), this->_map->getCameraRotation());

}

void GameObject::createPool()
{
    this->_camera->_gameObj = this;
    this->_map->_gameObj = this;
    for (size_t i = 0; i != this->_player.size(); i += 1)
        this->_player.at(i)->_gameObj = this;
    for (size_t i = 0; i != this->_ia.size(); i += 1)
        this->_ia.at(i)->_gameObj = this;
}

GameObject::GameObject(IrrlichtDevice *device, configBomberman_t *cf)
{
    this->_device = device;
    this->_sceneManager = device->getSceneManager();
    this->_videoDriver = device->getVideoDriver();
    this->_gui = device->getGUIEnvironment();
    this->_timer = device->getTimer();
    this->_timer->setTime(0);
    this->_configBbmCharacter = cf;

    createBombermanWithType();
    this->_camera = new Camera();
    this->_map = new Map();
}

GameObject::~GameObject()
{
    if (this->_player.size() != 0) {
        for (size_t i = this->_player.size() - 1; 1; i -= 1) {
            delete this->_player.at(i);
            this->_player.erase(this->_player.begin() + i);
            if (i == 0)
                break;
        }
    }
    if (this->_ia.size() != 0) {
        for (size_t i = this->_ia.size() - 1; 1; i -= 1) {
            delete this->_ia.at(i);
            this->_ia.erase(this->_ia.begin() + i);
            if (i == 0)
                break;
        }
    }
}