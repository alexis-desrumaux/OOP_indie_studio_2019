/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** event
*/

#ifndef EVENT_HPP_
#define EVENT_HPP_

#include <iostream>
#include "irrlicht.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class MyEventReceiver : public IEventReceiver
{
public:
    virtual bool OnEvent(const SEvent &event)
    {
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
            KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
        if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
            if (event.MouseInput.Event == EMIE_LMOUSE_PRESSED_DOWN)
                MouseIsDown = true;
            if (event.MouseInput.Event == EMIE_LMOUSE_LEFT_UP)
                MouseIsDown = false;
        }
        return false;
    }
    virtual bool IsKeyDown(EKEY_CODE keyCode) const
    {
        return KeyIsDown[keyCode];
    }
    virtual bool isMouseDown() const {
        return MouseIsDown;
    }
    MyEventReceiver()
    {
        for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
            KeyIsDown[i] = false;
        MouseIsDown = false;
    }

private:
    bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
    bool MouseIsDown;
};

#endif /* !EVENT_HPP_ */
