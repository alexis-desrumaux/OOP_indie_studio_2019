/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** main
*/

#include <iostream>
#include <fstream>
#include "include.hpp"
#include "Bomberman.hpp"

using namespace irr;
using namespace video;
using namespace scene;
using namespace core;
using namespace gui;

// This is the one method that we have to implement
Indie::Indie()
{
    this->state = this->Enum_bomberman.MENU;
    //this->bomberman = NULL;
    this->receiver = new MyEventReceiver();
    this->device = createDevice(EDT_OPENGL, dimension2d<u32>(1920, 1080), 32, false, false, true, this->receiver);
    this->driver = device->getVideoDriver();
    this->sceneManager = device->getSceneManager();
    this->my_launch_screen.gui = sceneManager->getGUIEnvironment();
    this->my_launch_screen.isInit = false;
    this->my_select_screen.gui = sceneManager->getGUIEnvironment();
    this->my_select_screen.isInit = false;
    this->my_pause_screen.gui = sceneManager->getGUIEnvironment();
    this->my_pause_screen.isInit = false;
    this->my_map_screen.gui = sceneManager->getGUIEnvironment();
    this->my_map_screen.isInit = false;
    this->musicMenu = new Music();
    this->selectedSound = new Music();
    this->musicMenu->newMusic("assets/music/menu.ogg");
    this->selectedSound->newMusic("assets/music/select.wav");
}

Indie::~Indie()
{
}

void Indie::init_select_screen()
{
    irr::gui::IGUIEnvironment *gui = this->device->getGUIEnvironment();

    this->my_select_screen.background = gui->addImage(driver->getTexture("./assets/selectPlayer_screen/wallpaper.jpg"), vector2di(0, 0), true, 0, -1, 0);

    this->my_select_screen.selectPlayerOne = gui->addImage(driver->getTexture("assets/character/bomby.png"), vector2di(300, 500), true, 0, -1, 0);
    this->my_select_screen.selectPlayerTwo = gui->addImage(driver->getTexture("assets/character/bomby.png"), vector2di(1200, 500), true, 0, -1, 0);

    this->my_select_screen.vsFaceOne = gui->addImage(driver->getTexture("assets/selectPlayer_screen/vs_face_revert.png"), vector2di(300, 0), true, 0, -1, 0);
    this->my_select_screen.vsFaceTwo = gui->addImage(driver->getTexture("assets/selectPlayer_screen/vs_face.png"), vector2di(1200, 0), true, 0, -1, 0);

    this->my_select_screen.vs = gui->addImage(driver->getTexture("assets/selectPlayer_screen/vs.png"), vector2di(830, 50), true, 0, -1, 0);

    this->my_select_screen.start = gui->addButton(rect<s32>(0, 0, 265, 105), 0, -1, L"");
    this->my_select_screen.start->setImage(this->driver->getTexture("./assets/selectPlayer_screen/buttonStartGray.png"));
    this->my_select_screen.start->setUseAlphaChannel(true);
    this->my_select_screen.start->setDrawBorder(false);
    this->my_select_screen.start->setRelativePosition(position2di(800, 325));
    this->my_select_screen.startBtn_isSet = false;


    this->my_select_screen.input_left = gui->addEditBox(L"", rect<s32>(0, 0, 200, 50));
    this->my_select_screen.input_right = gui->addEditBox(L"", rect<s32>(0, 0, 200, 50));
    this->my_select_screen.input_left->setMultiLine(false);
    this->my_select_screen.input_right->setMultiLine(false);
    this->my_select_screen.input_left->setVisible(true);
    this->my_select_screen.input_right->setVisible(true);
    this->my_select_screen.input_left->setRelativePosition(position2di(600, 100));
    this->my_select_screen.input_right->setRelativePosition(position2di(1050, 100));
    this->my_select_screen.input_left->setOverrideFont(gui->getFont("./assets/font/Bomberman/x12/Bomberman.xml"));
    this->my_select_screen.input_left->setOverrideColor(irr::video::SColor(255, 220, 20, 0));
    this->my_select_screen.input_right->setOverrideFont(gui->getFont("./assets/font/Bomberman/x12/Bomberman.xml"));
    this->my_select_screen.input_right->setOverrideColor(irr::video::SColor(255, 220, 20, 0));


    this->my_select_screen.typeOne = gui->addButton(rect<s32>(0, 0, 233, 79), 0, -1, L"");
    this->my_select_screen.typeOne->setImage(this->driver->getTexture("./assets/selectPlayer_screen/buttonPlayer.png"));
    this->my_select_screen.typeOne->setUseAlphaChannel(true);
    this->my_select_screen.typeOne->setDrawBorder(false);
    this->my_select_screen.typeOne->setRelativePosition(position2di(385, 425));
    this->my_select_screen.typeOne_enum = ObjType::Bomberman;

    this->my_select_screen.typeTwo = gui->addButton(rect<s32>(0, 0, 233, 79), 0, -1, L"");
    this->my_select_screen.typeTwo->setImage(this->driver->getTexture("./assets/selectPlayer_screen/buttonIA.png"));
    this->my_select_screen.typeTwo->setUseAlphaChannel(true);
    this->my_select_screen.typeTwo->setDrawBorder(false);
    this->my_select_screen.typeTwo->setRelativePosition(position2di(1280, 425));
    this->my_select_screen.typeTwo_enum = ObjType::BombermanIA;

    this->my_select_screen.cf = new configBomberman_t;

    this->my_select_screen.isInit = true;
}

void Indie::init_launch_screen()
{
    irr::gui::IGUIEnvironment *gui = this->device->getGUIEnvironment();
    irr::gui::IGUIFont *myFont = gui->getFont("./assets/font/Bomberman/x10/Bomberman.xml");

    this->my_launch_screen.background_menu = this->my_launch_screen.gui->addImage(driver->getTexture("./assets/launch_screen/background_space.png"), vector2di(0, 0), true, 0, -1, 0);

    this->my_launch_screen.Play_button = this->my_launch_screen.gui->addButton(rect<s32>(0, 0, 393, 122), 0, -1, L"");
    this->my_launch_screen.Play_button->setImage(this->driver->getTexture("./assets/launch_screen/buttonLaunch.png"));
    this->my_launch_screen.Play_button->setUseAlphaChannel(true);
    this->my_launch_screen.Play_button->setDrawBorder(false);
    this->my_launch_screen.Play_button->setRelativePosition(position2di(700, 400));

    this->my_launch_screen.resume_button = this->my_launch_screen.gui->addButton(rect<s32>(0, 0, 393, 122), 0, -1, L"");
    this->my_launch_screen.resume_button->setImage(this->driver->getTexture("./assets/launch_screen/buttonResume.png"));
    this->my_launch_screen.resume_button->setUseAlphaChannel(true);
    this->my_launch_screen.resume_button->setDrawBorder(false);
    this->my_launch_screen.resume_button->setRelativePosition(position2di(700, 550));

    this->my_launch_screen.Quit_button = this->my_launch_screen.gui->addButton(rect<s32>(0, 0, 393, 122), 0, -1, L"");
    this->my_launch_screen.Quit_button->setImage(this->driver->getTexture("./assets/launch_screen/buttonQuit.png"));
    this->my_launch_screen.Quit_button->setUseAlphaChannel(true);
    this->my_launch_screen.Quit_button->setDrawBorder(false);
    this->my_launch_screen.Quit_button->setRelativePosition(position2di(700, 700));

    this->my_launch_screen.nbPlayer = 0;
    this->my_launch_screen.isInit = true;
}

void Indie::init_map_screen()
{
    irr::gui::IGUIEnvironment *gui = this->device->getGUIEnvironment();
    this->my_map_screen.selected_text = gui->getFont("./assets/font/Bomberman/x10/Bomberman.xml");

    this->my_map_screen.go_button = this->my_map_screen.gui->addButton(rect<s32>(0, 0, 393, 122), 0, -1, L"");
    this->my_map_screen.go_button->setImage(this->driver->getTexture("./assets/selectPlayer_screen/buttonStart.png"));
    this->my_map_screen.go_button->setUseAlphaChannel(true);
    this->my_map_screen.go_button->setDrawBorder(false);
    this->my_map_screen.go_button->setRelativePosition(position2di(700, 700));

    this->my_map_screen.first_button = this->my_map_screen.gui->addButton(rect<s32>(0, 0, 500, 400), 0, -1, L"");
    this->my_map_screen.first_button->setImage(this->driver->getTexture("./assets/map/first.png"));
    this->my_map_screen.first_button->setUseAlphaChannel(true);
    this->my_map_screen.first_button->setDrawBorder(false);
    this->my_map_screen.first_button->setRelativePosition(position2di(50, 100));

    this->my_map_screen.second_button = this->my_map_screen.gui->addButton(rect<s32>(0, 0, 500, 400), 0, -1, L"");
    this->my_map_screen.second_button->setImage(this->driver->getTexture("./assets/map/second.png"));
    this->my_map_screen.second_button->setUseAlphaChannel(true);
    this->my_map_screen.second_button->setDrawBorder(false);
    this->my_map_screen.second_button->setRelativePosition(position2di(650, 100));

    this->my_map_screen.third_button = this->my_map_screen.gui->addButton(rect<s32>(0, 0, 500, 400), 0, -1, L"");
    this->my_map_screen.third_button->setImage(this->driver->getTexture("./assets/map/third.png"));
    this->my_map_screen.third_button->setUseAlphaChannel(true);
    this->my_map_screen.third_button->setDrawBorder(false);
    this->my_map_screen.third_button->setRelativePosition(position2di(1250, 100));

    this->my_map_screen.isInit = true;
}

void Indie::init_game()
{
    this->sceneManager->clear();
    this->bomberman = new Game(this->device, this->my_select_screen.cf, this->my_map_screen.selected);
    this->isGameInit = true;
}

void Indie::init_pause()
{
    irr::gui::IGUIEnvironment *gui = this->device->getGUIEnvironment();

    this->my_pause_screen.resume_button = this->my_pause_screen.gui->addButton(rect<s32>(0, 0, 393, 122), 0, -1, L"");
    this->my_pause_screen.resume_button->setImage(this->driver->getTexture("./assets/launch_screen/buttonResume.png"));
    this->my_pause_screen.resume_button->setUseAlphaChannel(true);
    this->my_pause_screen.resume_button->setDrawBorder(false);
    this->my_pause_screen.resume_button->setRelativePosition(position2di(700, 400));

    this->my_pause_screen.save_button = this->my_pause_screen.gui->addButton(rect<s32>(0, 0, 393, 122), 0, -1, L"");
    this->my_pause_screen.save_button->setImage(this->driver->getTexture("./assets/launch_screen/buttonSave.png"));
    this->my_pause_screen.save_button->setUseAlphaChannel(true);
    this->my_pause_screen.save_button->setDrawBorder(false);
    this->my_pause_screen.save_button->setRelativePosition(position2di(700, 550));

    this->my_pause_screen.home_button = this->my_pause_screen.gui->addButton(rect<s32>(0, 0, 393, 122), 0, -1, L"");
    this->my_pause_screen.home_button->setImage(this->driver->getTexture("./assets/launch_screen/buttonHome.png"));
    this->my_pause_screen.home_button->setUseAlphaChannel(true);
    this->my_pause_screen.home_button->setDrawBorder(false);
    this->my_pause_screen.home_button->setRelativePosition(position2di(700, 700));

    this->my_pause_screen.quit_button = this->my_pause_screen.gui->addButton(rect<s32>(0, 0, 393, 122), 0, -1, L"");
    this->my_pause_screen.quit_button->setImage(this->driver->getTexture("./assets/launch_screen/buttonQuit.png"));
    this->my_pause_screen.quit_button->setUseAlphaChannel(true);
    this->my_pause_screen.quit_button->setDrawBorder(false);
    this->my_pause_screen.quit_button->setRelativePosition(position2di(700, 850));

    this->my_pause_screen.isInit = true;
}

void Indie::core()
{
    this->musicMenu->playMusic();
    device->setEventReceiver(receiver);
    while (this->device->run()) {
        if (receiver->IsKeyDown(irr::KEY_KEY_P) && state != Enum_bomberman.MENU && state != Enum_bomberman.SELECT_PLAYER && state != Enum_bomberman.SELECT_MAP)
            this->state = Enum_bomberman.PAUSE;
        if (state == Enum_bomberman.MENU) {
            if (this->my_launch_screen.isInit == false)
                init_launch_screen();
            display_menu();
        }
        if (state == Enum_bomberman.SELECT_PLAYER) {
            if (this->my_select_screen.isInit == false)
                init_select_screen();
            display_select_nb_player();
        }
        if (state == Enum_bomberman.PLAY) {
            if (this->isGameInit == false)
                init_game();
            display_game();
        }
        if (state == Enum_bomberman.PAUSE) {
            if (this->my_pause_screen.isInit == false)
                init_pause();
            display_pause();
        }
        if (state == Enum_bomberman.SELECT_MAP) {
            if (this->my_map_screen.isInit == false)
                init_map_screen();
            display_map_screen();
        }
        /*if (state == Enum_bomberman.CONFIG_PLAYER)
            display_config();*/
        if (state == Enum_bomberman.QUIT)
            break;
        if (this->my_launch_screen.Quit_button->isPressed() == true)
            break;
    }
    this->musicMenu->stopMusic();
    delete this->musicMenu;
    delete this->selectedSound;
    //if (this->bomberman != NULL)
        delete this->bomberman;
    this->device->drop();
}

int main(void)
{
    Indie setup;

    setup.core();
    return 0;
}