/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Wall
*/

#include "Bomberman.hpp"

Point3D Wall::getPosition()
{
    return this->_pos;
}

void Wall::init(Point3D pos)
{
    this->_pos = pos;
    this->_sprite = this->_gameObj->_sceneManager->addAnimatedMeshSceneNode(this->_gameObj->_sceneManager->getMesh("./assets/Cube/Metal/metal.obj"));
    this->_sprite->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    this->_sprite->setPosition(vector3df(pos.x, pos.y, pos.z));
}

Wall::Wall(GameObject *gmo)
{
    this->_gameObj = gmo;
}

Wall::~Wall()
{
}
