/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Fireball
*/

#include "Bomberman.hpp"

bool Fireball::isSet()
{
}

void Fireball::destroy()
{
    this->_sprite->setVisible(false);
}

void Fireball::init(Point3D pos)
{
    this->_sprite->setPosition(vector3df(pos.x, pos.y, pos.z));
    this->_sprite->setVisible(true);
}

Fireball::Fireball(GameObject *gmo)
{
    this->_gameObj = gmo;
    this->_sprite = this->_gameObj->_sceneManager->addAnimatedMeshSceneNode(this->_gameObj->_sceneManager->getMesh("./assets/Bomb/bomb/Fireball/fire.obj"));
    this->_sprite->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    this->_sprite->setVisible(false);
}

Fireball::~Fireball()
{
}
