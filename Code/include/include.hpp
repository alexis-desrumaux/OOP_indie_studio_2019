/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** include
*/

#ifndef INCLUDE_HPP_
#define INCLUDE_HPP_

#include <iostream>
#include "Music.hpp"
#include <SFML/Audio.hpp>
#include "irrlicht.h"
#include "Bomberman.hpp"
#include "event.hpp"

class selectPlayerScreen {
    public:
        IGUIEnvironment *gui;
        IGUIEditBox *input_left;
        IGUIEditBox *input_right;
        IGUIImage *selectPlayerOne;
        IGUIImage *selectPlayerTwo;
        IGUIImage *background;
        IGUIImage *vsFaceOne;
        IGUIImage *vsFaceTwo;
        IGUIImage *vs;
        IGUIButton *typeOne;
        IGUIButton *typeTwo;
        IGUIButton *start;
        ObjType typeOne_enum;
        ObjType typeTwo_enum;
        configBomberman_t *cf;
        bool typeOneBtn_isPressed;
        bool typeTwoBtn_isPressed;
        bool startBtn_isSet;
        bool isInit;
};

class selectMapScreen {
    public:
        IGUIEnvironment *gui;
        IGUIFont *selected_text;
        IGUIButton *go_button;
        IGUIButton *first_button;
        IGUIButton *second_button;
        IGUIButton *third_button;
        bool isInit;
        int selected;
};

class LaunchScreen {
    public:
        int nbPlayer;
        IGUIEnvironment *gui;
        SEvent event;
        IGUIButton *Play_button;
        IGUIButton *Quit_button;
        IGUIButton *resume_button;
        IGUIImage *background_menu;
        bool isInit;
};

class GameScreen {
    public:
        IGUIEnvironment *gui;
        SEvent event;
        ITexture *selectPlayer;
        gui::IGUIFont* press_to_exit;
};

class PauseScreen {
    public:
        IGUIEnvironment *gui;
        SEvent event;
        ITexture *pause;
        IGUIButton *save_button;
        IGUIButton *quit_button;
        IGUIButton *resume_button;
        IGUIButton *home_button;
        bool isInit;
};

class Enum {
    public:
        enum {
            GUI_ID_QUIT_BUTTON = 101,
            GUI_ID_NEW_WINDOW_BUTTON,
            GUI_ID_FILE_OPEN_BUTTON,
            GUI_ID_TRANSPARENCY_SCROLL_BAR
        };
        enum {
            MENU,
            SELECT_PLAYER,
            PLAY,
            QUIT,
            PAUSE,
            CONFIG_PLAYER,
            SELECT_MAP,
        };
};

class Indie {
    public:
    //functions
        Indie();
        ~Indie();
        void core();
        void init_game();
        void init_launch_screen();
        void init_select_screen();
        void init_pause();
        void init_map_screen();

        void display_menu();
        void display_pause();
        void display_game();
        void display_config();
        void display_select_nb_player();
        void display_select_nb_player_manage_btn();
        void display_select_nb_player_manage_startBtn();
        void display_button_pause();
        void display_button_game();
        void display_map_screen();

        void hide_button_menu();
        void hide_button_pause();
        void hide_button_game();
        void hide_button_select_nb_player();
    //data
    private:
    //functions
    //data
        IrrlichtDevice *device;
        IVideoDriver *driver;
        ISceneManager *sceneManager;
        MyEventReceiver *receiver;
        LaunchScreen my_launch_screen;
        selectPlayerScreen my_select_screen;
        PauseScreen my_pause_screen;
        selectMapScreen my_map_screen;
        Enum Enum_bomberman;
        Music *musicMenu;
        Music *selectedSound;
        int state;
        u32 lastime;
        Game *bomberman;
        bool isGameInit;
};

#endif /* !INCLUDE_HPP_ */
