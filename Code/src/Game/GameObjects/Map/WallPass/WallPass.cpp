/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** WallPass
*/

#include "Bomberman.hpp"

Point3D WallPass::getPosition()
{
    return this->_pos;
}

void WallPass::init(Point3D pos)
{
    this->_pos = pos;
    this->_rect = {0, 2, 0, 2, 0, 2};
}

WallPass::WallPass(GameObject *gmo)
{
    this->_gameObj = gmo;
}

WallPass::~WallPass()
{
}
