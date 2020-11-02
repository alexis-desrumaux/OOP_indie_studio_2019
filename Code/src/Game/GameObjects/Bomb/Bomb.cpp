/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Bomb
*/

#include "Bomberman.hpp"

bool Bomb::isExplode()
{
    return this->_explode;
}

bool Bomb::isSet()
{
    return this->_isInit;
}

void Bomb::destroy_fireball()
{
    for (size_t i = 0; i != this->_fireballs_left.size(); i += 1) {
        this->_fireballs_left.at(i)->destroy();
    }
    for (size_t i = 0; i != this->_fireballs_right.size(); i += 1) {
        this->_fireballs_right.at(i)->destroy();
    }
    for (size_t i = 0; i != this->_fireballs_forward.size(); i += 1) {
        this->_fireballs_forward.at(i)->destroy();
    }
    for (size_t i = 0; i != this->_fireballs_backward.size(); i += 1) {
        this->_fireballs_backward.at(i)->destroy();
    }
}

void Bomb::compute_fireball()
{
    Point3D posFireballLeft = {this->_pos.x, this->_pos.y, this->_pos.z};
    Point3D posFireballRight = {this->_pos.x, this->_pos.y, this->_pos.z};
    Point3D posFireballForward = {this->_pos.x, this->_pos.y, this->_pos.z};
    Point3D posFireballBackward = {this->_pos.x, this->_pos.y, this->_pos.z};

    for (size_t i = 0; i != this->_fireballs_left.size(); i += 1) {
        posFireballLeft.x -= 2;
        this->_fireballs_left.at(i)->init(posFireballLeft);
    }
    for (size_t i = 0; i != this->_fireballs_right.size(); i += 1) {
        posFireballRight.x += 2;
        this->_fireballs_right.at(i)->init(posFireballRight);
    }
    for (size_t i = 0; i != this->_fireballs_forward.size(); i += 1) {
        posFireballForward.z += 2;
        this->_fireballs_forward.at(i)->init(posFireballForward);
    }
    for (size_t i = 0; i != this->_fireballs_backward.size(); i += 1) {
        posFireballBackward.z -= 2;
        this->_fireballs_backward.at(i)->init(posFireballBackward);
    }
}

void Bomb::compute()
{
    irr::u32 relativeExplodeTime = this->_gameObj->_timer->getTime() - this->_explodeTimer;
    irr::u32 relativeAnimTime = this->_gameObj->_timer->getTime() - this->_animTimer;

    if (relativeExplodeTime >= 5000 && relativeExplodeTime < 6000) {
        if (this->_playSound == false) {
            this->_sound->playMusic();
            this->_playSound = true;
        }
        compute_fireball();
    }
    if (relativeExplodeTime >= 6000) {
        destroy_fireball();
        this->_explode = true;
        this->_explodeTimer = this->_gameObj->_timer->getTime();
    }
    if (relativeAnimTime >= 0 && relativeAnimTime < 1000) {
        this->_scale.x += 0.005;
        this->_scale.y += 0.005;
        this->_scale.z += 0.005;
        this->_sprite->setScale(vector3df(this->_scale.x, this->_scale.y, this->_scale.z));
    }
    if (relativeAnimTime >= 1000 && relativeAnimTime < 2000) {
        this->_scale.x -= 0.005;
        this->_scale.y -= 0.005;
        this->_scale.z -= 0.005;
        this->_sprite->setScale(vector3df(this->_scale.x, this->_scale.y, this->_scale.z));
    }
    if (relativeAnimTime >= 2000) {
        this->_animTimer = this->_gameObj->_timer->getTime();
    }

}

void Bomb::destroy()
{
    this->_sprite->setVisible(false);
    this->_isInit = false;
}

void Bomb::init(Point3D pos, int radius)
{
    Fireball *c = NULL;

    this->_pos = pos;
    this->_scale = {1.0f, 1.0f, 1.0f};
    this->_sprite->setVisible(true);
    this->_sprite->setPosition(vector3df(pos.x, pos.y, pos.z));

    if (this->_radius < radius) {
        for (; this->_radius != radius; this->_radius += 1) {
            this->_fireballs_left.push_back(new Fireball(this->_gameObj));
            this->_fireballs_right.push_back(new Fireball(this->_gameObj));
            this->_fireballs_forward.push_back(new Fireball(this->_gameObj));
            this->_fireballs_backward.push_back(new Fireball(this->_gameObj));
        }
    }
    this->_playSound = false;
    this->_explodeTimer = this->_gameObj->_timer->getTime();
    this->_animTimer = this->_gameObj->_timer->getTime();
    this->_explode = false;
    this->_isInit = true;
}

Bomb::Bomb(GameObject *gmo)
{
    this->_gameObj = gmo;
    this->_sprite = NULL;
    this->_sprite = this->_gameObj->_sceneManager->addAnimatedMeshSceneNode(this->_gameObj->_sceneManager->getMesh("./assets/Bomb/bomb/Bomb.obj"));
    this->_sprite->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    this->_sprite->setVisible(false);
    this->_sound = new Music();
    this->_sound->newMusic("./assets/Bomb/bomb/Sound/default.ogg");
    this->_radius = 0;
    this->_isInit = false;
}

Bomb::~Bomb()
{
    if (this->_fireballs_left.size() != 0) {
        for (size_t i = this->_fireballs_left.size() - 1; 1; i -= 1) {
            delete this->_fireballs_left.at(i);
            this->_fireballs_left.erase(this->_fireballs_left.begin() + i);
            if (i == 0)
                break;
        }
    }
    if (this->_fireballs_right.size() != 0) {
        for (size_t i = this->_fireballs_right.size() - 1; 1; i -= 1) {
            delete this->_fireballs_right.at(i);
            this->_fireballs_right.erase(this->_fireballs_right.begin() + i);
            if (i == 0)
                break;
        }
    }
    if (this->_fireballs_forward.size() != 0) {
        for (size_t i = this->_fireballs_forward.size() - 1; 1; i -= 1) {
            delete this->_fireballs_forward.at(i);
            this->_fireballs_forward.erase(this->_fireballs_forward.begin() + i);
            if (i == 0)
                break;
        }
    }
    if (this->_fireballs_backward.size() != 0) {
        for (size_t i = this->_fireballs_backward.size() - 1; 1; i -= 1) {
            delete this->_fireballs_backward.at(i);
            this->_fireballs_backward.erase(this->_fireballs_backward.begin() + i);
            if (i == 0)
                break;
        }
    }
    if (this->_sound != NULL) {
        this->_sound->stopSound();
        delete this->_sound;
    }
}
