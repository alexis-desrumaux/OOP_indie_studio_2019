/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Bomberman
*/

#include "Bomberman.hpp"

void Bomberman::setBombAt(Point3D pos)
{
    for (size_t i = 0; i != this->_bombs.size(); i += 1) {
        if (this->_bombs.at(i)->isSet() == false) {
            this->_bombs.at(i)->init(pos, 4);
            break;
        }
    }
}

Direction Bomberman::getCurrentDir()
{
    return this->_currentDir;
}

void Bomberman::moveDown(irr::f32 speed)
{
    this->_pos.z -= speed;

    if (this->_currentDir == Direction::Left)
        this->_rot.y -= 90;
    if (this->_currentDir == Direction::Right) {
        this->_rot.y += 90;
        //this->_pos.x -= 1;
    }
    if (this->_currentDir == Direction::Up) {
        this->_rot.y += 180;
        //this->_pos.z -= 1;
    }
    this->_sprite->setPosition(vector3df(this->_pos.x, this->_pos.y, this->_pos.z));
    this->_sprite->setRotation(vector3df(this->_rot.x, this->_rot.y, this->_rot.z));
    this->_currentDir = Direction::Down;
}

void Bomberman::moveUp(irr::f32 speed)
{
    this->_pos.z += speed;

    if (this->_currentDir == Direction::Down) {
        this->_rot.y -= 180;
    }
    else if (this->_currentDir == Direction::Left)
        this->_rot.y += 90;
    else if (this->_currentDir == Direction::Right)
        this->_rot.y -= 90;
    if (this->_rot.y == 360)
        this->_rot.y = 0;
    this->_sprite->setPosition(vector3df(this->_pos.x, this->_pos.y, this->_pos.z));
    this->_sprite->setRotation(vector3df(this->_rot.x, this->_rot.y, this->_rot.z));
    this->_currentDir = Direction::Up;
}

void Bomberman::moveRight(irr::f32 speed)
{
    this->_pos.x += speed;

    if (this->_currentDir == Direction::Down)
        this->_rot.y -= 90;
    else if (this->_currentDir == Direction::Up)
        this->_rot.y += 90;
    else if (this->_currentDir == Direction::Left) {
        this->_rot.y -= 180;
    }
    if (this->_rot.y == 360)
        this->_rot.y = 0;
    this->_sprite->setPosition(vector3df(this->_pos.x, this->_pos.y, this->_pos.z));
    this->_sprite->setRotation(vector3df(this->_rot.x, this->_rot.y, this->_rot.z));
    this->_currentDir = Direction::Right;
}

void Bomberman::moveLeft(irr::f32 speed)
{

    this->_pos.x -= speed;

    if (this->_currentDir == Direction::Down) {
        this->_rot.y += 90;
    }
    else if (this->_currentDir == Direction::Up) {
        this->_rot.y += 270;
    }
    else if (this->_currentDir == Direction::Right) {
        this->_rot.y += 180;
    }
    if (this->_rot.y == 360)
        this->_rot.y = 0;
    this->_sprite->setPosition(vector3df(this->_pos.x, this->_pos.y, this->_pos.z));
    this->_sprite->setRotation(vector3df(this->_rot.x, this->_rot.y, this->_rot.z));
    this->_currentDir = Direction::Left;
}

void Bomberman::move(Direction dir, irr::f32 speed)
{
    if (dir == Direction::Left) {
        moveLeft(speed);
    }
    else if (dir == Direction::Right) {
        moveRight(speed);
    }
    else if (dir == Direction::Up) {
        moveUp(speed);
    }
    else if (dir == Direction::Down) {
        moveDown(speed);
    }
}

void Bomberman::compute_bomb()
{
    for (size_t i = 0; i != this->_bombs.size(); i += 1) {
        if (this->_bombs.at(i)->isSet()) {
            this->_bombs.at(i)->compute();
        }
    }
    for (size_t i = 0; i != this->_bombs.size(); i += 1) {
        if (this->_bombs.at(i)->isSet() && this->_bombs.at(i)->isExplode()) {
            this->_bombs.at(i)->destroy();
        }
    }
}

void Bomberman::compute_keySetBomb(MyEventReceiver *event)
{
    if (event->IsKeyDown(this->_keyLayout.SetBomb) && this->_pressSetBomb == false) {
        setBombAt(this->_pos);
        this->_pressSetBomb = true;
    }
    if (!event->IsKeyDown(this->_keyLayout.SetBomb) && this->_pressSetBomb == true)
        this->_pressSetBomb = false;
}

int Bomberman::compute(MyEventReceiver *event)
{
    vector3df pos = this->_sprite->getAbsolutePosition();

    if (event->IsKeyDown(this->_keyLayout.Left)) {
        move(Direction::Left, 0.2);
    }
    else if (event->IsKeyDown(this->_keyLayout.Right)) {
        move(Direction::Right, 0.2);
    }
    else if (event->IsKeyDown(this->_keyLayout.Down)) {
        move(Direction::Down, 0.2);
    }
    else if (event->IsKeyDown(this->_keyLayout.Up)) {
        move(Direction::Up, 0.2);
    }
    compute_keySetBomb(event);

    compute_bomb();
    return 0;
}

void Bomberman::init(std::wstring name, Point3D pos, KeyLayout keyLayout)
{
    this->_name = name;
    this->_pos = pos;
    this->_keyLayout = keyLayout;
    this->_rot = {0.0f, 180.0f, 0};
    this->_isAlive = 1;
    this->_pressSetBomb = false;
    this->_currentDir = Direction::Down;
    this->_bombs.push_back(new Bomb(this->_gameObj));
    this->_bombs.push_back(new Bomb(this->_gameObj));
    this->_bombs.push_back(new Bomb(this->_gameObj));
    this->_bombs.push_back(new Bomb(this->_gameObj));


    this->_sprite = this->_gameObj->_sceneManager->addAnimatedMeshSceneNode(this->_gameObj->_sceneManager->getMesh("./assets/character/bomberman_1.0.9.obj"));
    this->_sprite->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    this->_sprite->setPosition(vector3df(pos.x, pos.y, pos.z));
    this->_sprite->setRotation(vector3df(this->_rot.x, this->_rot.y, this->_rot.z));
}

Bomberman::Bomberman()
{
}

Bomberman::~Bomberman()
{
    if (this->_bombs.size() != 0) {
        for (size_t i = this->_bombs.size() - 1; 1; i -= 1) {
            delete this->_bombs.at(i);
            this->_bombs.erase(this->_bombs.begin() + i);
            if (i == 0)
                break;
        }
    }
}
