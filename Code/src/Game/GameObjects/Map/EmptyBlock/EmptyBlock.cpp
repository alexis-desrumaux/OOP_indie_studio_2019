/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EmptyBlock
*/

#include "Bomberman.hpp"

Point3D EmptyBlock::getPosition()
{
    return this->_pos;
}

void EmptyBlock::init(Point3D pos)
{
    this->_pos = pos;
    this->_rect = {0, 2, 0, 2, 0, 2};
}

EmptyBlock::EmptyBlock(GameObject *gmo)
{
    this->_gameObj = gmo;
}

EmptyBlock::~EmptyBlock()
{
}
