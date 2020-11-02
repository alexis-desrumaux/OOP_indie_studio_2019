/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** DBlock
*/

#include "Bomberman.hpp"

Point3D DBlock::getPosition()
{
    return this->_pos;
}

void DBlock::init(Point3D pos)
{
    this->_pos = pos;
    this->_sprite = this->_gameObj->_sceneManager->addAnimatedMeshSceneNode(this->_gameObj->_sceneManager->getMesh("./assets/Cube/Brick/brick.obj"));
    this->_sprite->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    this->_sprite->setPosition(vector3df(pos.x, pos.y, pos.z));
}

DBlock::DBlock(GameObject *gmo)
{
    this->_gameObj = gmo;
}

DBlock::~DBlock()
{
}
