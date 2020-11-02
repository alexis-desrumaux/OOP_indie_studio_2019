/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Buttons
*/

#include <iostream>
#include <fstream>
#include "include.hpp"

using namespace irr;
using namespace video;
using namespace scene;
using namespace core;
using namespace gui;

void Indie::hide_button_select_nb_player()
{
    my_select_screen.input_left->setVisible(false);
    my_select_screen.input_right->setVisible(false);
}

void Indie::hide_button_menu()
{
    my_launch_screen.Play_button->setVisible(false);
    my_launch_screen.Quit_button->setVisible(false);
    my_launch_screen.resume_button->setVisible(false);
}

void Indie::hide_button_pause()
{
    my_pause_screen.resume_button->grab();
    my_pause_screen.resume_button->setVisible(false);
    my_pause_screen.quit_button->grab();
    my_pause_screen.quit_button->setVisible(false);
    my_pause_screen.save_button->grab();
    my_pause_screen.save_button->setVisible(false);
    my_pause_screen.home_button->grab();
    my_pause_screen.home_button->setVisible(false);
}

void Indie::display_button_pause()
{
    my_pause_screen.resume_button->grab();
    my_pause_screen.resume_button->setVisible(true);
    my_pause_screen.quit_button->grab();
    my_pause_screen.quit_button->setVisible(true);
    my_pause_screen.save_button->grab();
    my_pause_screen.save_button->setVisible(true);
    my_pause_screen.home_button->grab();
    my_pause_screen.home_button->setVisible(true);
}

void Indie::hide_button_game()
{

}

void Indie::display_button_game()
{

}