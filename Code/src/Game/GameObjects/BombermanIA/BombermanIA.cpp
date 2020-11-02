/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** BombermanIA
*/

#include "Bomberman.hpp"

int BombermanIA::compute()
{
    return 0;
}

void BombermanIA::init(std::wstring name, Point3D pos)
{
    this->_pos = pos;
    this->_name = name;
    this->_isAlive = 1;

    this->_sprite = this->_gameObj->_sceneManager->addAnimatedMeshSceneNode(this->_gameObj->_sceneManager->getMesh("./assets/character/bomberman_1.0.9.obj"));
    this->_sprite->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    this->_sprite->setPosition(vector3df(pos.x, pos.y, pos.z));
    this->_sprite->setRotation(vector3df(0.0f, 180.0f, 0));
}

BombermanIA::BombermanIA()
{
}

BombermanIA::~BombermanIA()
{
}
