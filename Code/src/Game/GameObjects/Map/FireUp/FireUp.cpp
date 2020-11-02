/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** FireUp
*/

#include "Bomberman.hpp"

Point3D FireUp::getPosition()
{
    return this->_pos;
}

void FireUp::init(Point3D pos)
{
    this->_pos = pos;
    this->_rect = {0, 2, 0, 2, 0, 2};
}

FireUp::FireUp(GameObject *gmo)
{
    this->_gameObj = gmo;
}

FireUp::~FireUp()
{
}
