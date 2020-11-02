/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Camera
*/

#include "Bomberman.hpp"

void Camera::compute(MyEventReceiver *event)
{
    vector3df pos = this->camera->getAbsolutePosition();
    vector3df tar = this->camera->getTarget();

    //std::cout << "Camera => x: " << pos.X << " y: " << pos.Y << " z: " << pos.Z << std::endl;
    //std::cout << "Target => x: " << tar.X << " y: " << tar.Y << " z: " << tar.Z << std::endl;
    return;
}

void Camera::setKeyMap()
{
    this->keyMap[0].Action = irr::EKA_MOVE_FORWARD;  // avancer
    this->keyMap[0].KeyCode = irr::KEY_UP;
    this->keyMap[1].Action = irr::EKA_MOVE_BACKWARD; // reculer
    this->keyMap[1].KeyCode = irr::KEY_DOWN;
    this->keyMap[2].Action = irr::EKA_STRAFE_LEFT;   // a gauche
    this->keyMap[2].KeyCode = irr::KEY_LEFT;
    this->keyMap[3].Action = irr::EKA_STRAFE_RIGHT;  // a droite
    this->keyMap[3].KeyCode = irr::KEY_RIGHT;
    this->keyMap[4].Action = irr::EKA_JUMP_UP;  // saut
    this->keyMap[4].KeyCode = irr::KEY_SPACE;
}

void Camera::init(Point3D pos, Point3D rot)
{
    this->_pos = pos;
    this->_rot = rot;
    this->camera = this->_gameObj->_sceneManager->addCameraSceneNode(0, vector3df(pos.x, pos.y, pos.z), vector3df(rot.x, rot.y, rot.z), -1, true);

    //setKeyMap();
    //this->camera = this->_gameObj->_sceneManager->addCameraSceneNodeFPS(0, 100.0f, 0.1f, -1, this->keyMap, 5);
    /*this->camera->setPosition(vector3df(pos.x, pos.y, pos.z));
    this->camera->setRotation(vector3df(rot.x, rot.y, rot.z));
    this->camera->setTarget(vector3df(rot.x, rot.y, rot.z));*/

}

Camera::Camera()
{
}

Camera::~Camera()
{
}
