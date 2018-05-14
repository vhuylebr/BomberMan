/*
** EPITECH PROJECT, 2018
** Indie studio
** File description:
** MenuItem implementation
*/

#include "MenuItem.hpp"

MenuItem::MenuItem()
    : _selected(false)
{
}

void MenuItem::setCoord(unsigned char x, unsigned char y)
{
    _coord = std::make_pair(x, y);
}

void MenuItem::setSize(unsigned char x, unsigned char y)
{
    _size = std::make_pair(x, y);
}