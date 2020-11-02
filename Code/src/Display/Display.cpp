/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Display
*/

#include <iostream>
#include <fstream>
#include "include.hpp"

using namespace irr;
using namespace video;
using namespace scene;
using namespace core;
using namespace gui;

void Indie::display_menu()
{
    std::ifstream f("save.txt");
    if (!f.good())
        my_launch_screen.resume_button->setVisible(false);
    this->driver->beginScene(true, true);
    this->my_launch_screen.gui->drawAll();
    this->driver->endScene();
    if (this->my_launch_screen.Quit_button->isPressed()) {
        this->selectedSound->playMusic();
        this->state = Enum_bomberman.QUIT;
    }
    if (this->my_launch_screen.resume_button->isPressed()) {
        this->selectedSound->playMusic();
    }
    if (receiver->IsKeyDown(irr::KEY_RETURN) || this->my_launch_screen.Play_button->isPressed()) {
        this->selectedSound->playMusic();
        hide_button_menu();
        this->state = Enum_bomberman.SELECT_PLAYER;
    }
}

void Indie::display_game()
{
    this->bomberman->update(this->receiver);
}

void Indie::display_pause()
{
    this->driver->beginScene(true, true);
    this->my_pause_screen.gui->drawAll();
    this->driver->endScene();
    if (this->my_pause_screen.quit_button->isPressed()) {
        this->selectedSound->playMusic();
        this->state = Enum_bomberman.QUIT;
    }
    if (this->my_pause_screen.home_button->isPressed()) {
        this->selectedSound->playMusic();
        this->my_launch_screen.isInit = false;
        this->my_select_screen.isInit = false;
        this->my_pause_screen.isInit = false;
        this->my_map_screen.isInit = false;
        this->isGameInit = false;
        this->state = Enum_bomberman.MENU;
    }
    if (receiver->IsKeyDown(irr::KEY_ESCAPE) || this->my_pause_screen.resume_button->isPressed())
        this->state = Enum_bomberman.PLAY;
    if (this->my_pause_screen.save_button->isPressed()) {
        this->selectedSound->playMusic();
        std::ofstream save;
        save.open("save.txt");
        save.close();
    }
}

void Indie::display_map_screen()
{
    this->driver->beginScene(true, true);
    this->my_map_screen.gui->drawAll();
    stringw str = L"Selected map: ";
    if (this->my_map_screen.selected == 1)
        str += "First";
    if (this->my_map_screen.selected == 2)
        str += "Second";
    if (this->my_map_screen.selected == 3)
        str += "Third";
    this->my_map_screen.selected_text->draw(str.c_str(),core::rect<s32>(800,600,0,0),video::SColor(255,255,255,255));
    this->driver->endScene();
    if (this->my_map_screen.go_button->isPressed()) {
        this->selectedSound->playMusic();
        this->my_map_screen.go_button->setVisible(false);
        this->my_map_screen.first_button->setVisible(false);
        this->my_map_screen.second_button->setVisible(false);
        this->my_map_screen.third_button->setVisible(false);
        this->state = Enum_bomberman.PLAY;
    }
    if (this->my_map_screen.first_button->isPressed())
        this->my_map_screen.selected = 1;
    if (this->my_map_screen.second_button->isPressed())
        this->my_map_screen.selected = 2;
    if (this->my_map_screen.third_button->isPressed())
        this->my_map_screen.selected = 3;
}

void Indie::display_config()
{
    /*display_button_pause();
    hide_button_menu();
    hide_button_select_nb_player();
    this->driver->makeColorKeyTexture(my_pause_screen.pause, position2d<s32>(0, 0));
    this->driver->beginScene(true, true);
    this->driver->draw2DImage(my_pause_screen.pause, position2d<s32>(1536 / 2 - 200, 200), rect<s32>(0, 0, 400, 200));
    my_pause_screen.gui->drawAll();
    this->driver->endScene();
    if (this->my_pause_screen.quit_button->isPressed()) {
        this->selectedSound->playMusic();
        this->state = Enum_bomberman.QUIT;
    }
    if (this->my_pause_screen.home_button->isPressed()) {
        this->selectedSound->playMusic();
        this->state = Enum_bomberman.MENU;
    }
    if (receiver->IsKeyDown(irr::KEY_ESCAPE) || this->my_pause_screen.resume_button->isPressed())
        this->state = Enum_bomberman.PLAY;
    if (this->my_pause_screen.save_button->isPressed()) {
        this->selectedSound->playMusic();
        std::ofstream save;
        save.open("save.txt");
        save.close();
    }*/
}

void Indie::display_select_nb_player_manage_startBtn()
{
    const wchar_t *inputLeft = this->my_select_screen.input_left->getText();
    const wchar_t *inputRight = this->my_select_screen.input_right->getText();

    if (inputLeft != NULL && inputRight != NULL) {
        if (inputLeft[0] != '\0' && inputRight[0] != '\0') {
            if (this->my_select_screen.startBtn_isSet == false) {
                this->my_select_screen.start->setImage(this->driver->getTexture("./assets/selectPlayer_screen/buttonStart.png"));
                this->my_select_screen.start->setPressedImage(this->driver->getTexture("./assets/selectPlayer_screen/buttonStart.png"));
                this->my_select_screen.startBtn_isSet = true;
            }
        }
        else {
            if (this->my_select_screen.startBtn_isSet == true) {
                this->my_select_screen.start->setImage(this->driver->getTexture("./assets/selectPlayer_screen/buttonStartGray.png"));
                this->my_select_screen.start->setPressedImage(this->driver->getTexture("./assets/selectPlayer_screen/buttonStartGray.png"));
                this->my_select_screen.startBtn_isSet = false;
            }
        }
    }
    if (this->my_select_screen.startBtn_isSet && this->my_select_screen.start->isPressed()) {
        std::cout << "START GAME" << std::endl;
        this->my_select_screen.background->setVisible(false);
        this->my_select_screen.input_left->setVisible(false);
        this->my_select_screen.input_right->setVisible(false);
        this->my_select_screen.selectPlayerOne->setVisible(false);
        this->my_select_screen.selectPlayerTwo->setVisible(false);
        this->my_select_screen.start->setVisible(false);
        this->my_select_screen.typeOne->setVisible(false);
        this->my_select_screen.typeTwo->setVisible(false);
        this->my_select_screen.vs->setVisible(false);
        this->my_select_screen.vsFaceOne->setVisible(false);
        this->my_select_screen.vsFaceTwo->setVisible(false);
        this->my_select_screen.cf->BombermanOne = this->my_select_screen.typeOne_enum;
        this->my_select_screen.cf->BombermanTwo = this->my_select_screen.typeTwo_enum;
        this->my_select_screen.cf->BombermanOneName = std::wstring(this->my_select_screen.input_left->getText());
        this->my_select_screen.cf->BombermanTwoName = std::wstring(this->my_select_screen.input_right->getText());
        this->state = this->Enum_bomberman.SELECT_MAP;
    }
}

void Indie::display_select_nb_player_manage_btn()
{
    if (this->my_select_screen.typeOne->isPressed() && this->my_select_screen.typeOneBtn_isPressed == false) {
        if (this->my_select_screen.typeOne_enum == ObjType::Bomberman) {
            this->my_select_screen.typeOne->setImage(this->driver->getTexture("./assets/selectPlayer_screen/buttonIA.png"));
            this->my_select_screen.typeOne_enum = ObjType::BombermanIA;
        }
        else if (this->my_select_screen.typeOne_enum == ObjType::BombermanIA) {
            this->my_select_screen.typeOne->setImage(this->driver->getTexture("./assets/selectPlayer_screen/buttonPlayer.png"));
            this->my_select_screen.typeOne_enum = ObjType::Bomberman;
        }
        this->my_select_screen.typeOneBtn_isPressed = true;
    }
    else if (!this->my_select_screen.typeOne->isPressed())
        this->my_select_screen.typeOneBtn_isPressed = false;
    if (this->my_select_screen.typeTwo->isPressed() && this->my_select_screen.typeTwoBtn_isPressed == false) {
        if (this->my_select_screen.typeTwo_enum == ObjType::Bomberman) {
            this->my_select_screen.typeTwo->setImage(this->driver->getTexture("./assets/selectPlayer_screen/buttonIA.png"));
            this->my_select_screen.typeTwo_enum = ObjType::BombermanIA;
        }
        else if (this->my_select_screen.typeTwo_enum == ObjType::BombermanIA) {
            this->my_select_screen.typeTwo->setImage(this->driver->getTexture("./assets/selectPlayer_screen/buttonPlayer.png"));
            this->my_select_screen.typeTwo_enum = ObjType::Bomberman;
        }
        this->my_select_screen.typeTwoBtn_isPressed = true;
    }
    else if (!this->my_select_screen.typeTwo->isPressed()) {
        this->my_select_screen.typeTwoBtn_isPressed = false;
    }
}

void Indie::display_select_nb_player()
{
    this->sceneManager->clear();
    this->driver->beginScene(true, true);
    this->my_select_screen.gui->drawAll();
    this->driver->endScene();
    display_select_nb_player_manage_btn();
    display_select_nb_player_manage_startBtn();
}