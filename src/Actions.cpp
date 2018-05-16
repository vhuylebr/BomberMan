/*
** EPITECH PROJECT, 2018
** Indie Studio
** File description:
** clear actions
*/

#include "Actions.hpp"

void    clearAction(Actions &actions)
{
    actions.up = false;
    actions.down = false;
    actions.right = false;
    actions.left = false;
    actions.space = false;
    actions.escape = false;
	actions.buttonPressed = -1;
}

void displayAction(Actions &actions)
{
    (void)actions;
}