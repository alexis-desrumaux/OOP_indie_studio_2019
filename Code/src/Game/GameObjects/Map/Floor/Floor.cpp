/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Floor
*/

#include "Bomberman.hpp"

Point3D Floor::getPosition()
{
    return this->_pos;
}

void Floor::init(Point3D pos)
{
    this->_pos = pos;
    this->_sprite = this->_gameObj->_sceneManager->addAnimatedMeshSceneNode(this->_gameObj->_sceneManager->getMesh("./assets/Cube/Grass/grass.obj"));
    this->_sprite->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    this->_sprite->setPosition(vector3df(pos.x, pos.y, pos.z));
}

Floor::Floor(GameObject *gmo)
{
    this->_gameObj = gmo;
}

Floor::~Floor()
{
    this->_sprite->remove();
}
