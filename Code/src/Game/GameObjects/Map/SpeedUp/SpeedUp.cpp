/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SpeedUp
*/

#include "Bomberman.hpp"

Point3D SpeedUp::getPosition()
{
    return this->_pos;
}

void SpeedUp::init(Point3D pos)
{
    this->_pos = pos;
    this->_rect = {0, 2, 0, 2, 0, 2};
}

SpeedUp::SpeedUp(GameObject *gmo)
{
    this->_gameObj = gmo;
}

SpeedUp::~SpeedUp()
{
}
