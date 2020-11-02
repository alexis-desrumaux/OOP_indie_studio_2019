/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** BombUp
*/

#include "Bomberman.hpp"

Point3D BombUp::getPosition()
{
    return this->_pos;
}

void BombUp::init(Point3D pos)
{
    this->_pos = pos;
    this->_rect = {0, 2, 0, 2, 0, 2};
}

BombUp::BombUp(GameObject *gmo)
{
    this->_gameObj = gmo;
}

BombUp::~BombUp()
{
}
