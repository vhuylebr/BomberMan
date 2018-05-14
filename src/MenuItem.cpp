/*
** EPITECH PROJECT, 2018
** Indie studio
** File description:
** MenuItem implementation
*/

#include "MenuItem.hpp"

MenuItem::MenuItem(std::string text)
    : _selected(false), _text(text)
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