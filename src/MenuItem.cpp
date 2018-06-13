/*
** EPITECH PROJECT, 2018
** Indie studio
** File description:
** MenuItem implementation
*/

#include "MenuItem.hpp"

MenuItem::MenuItem(std::string text)
    : _stateTexture(false), _texture(std::string()), _text(text), _selected(false)
{
}

MenuItem::MenuItem(Entity type, int id, std::string text, ui x, ui y, ui lenght, ui height)
	: _stateTexture(false), _texture(std::string()), _type(type), _id(id), _text(text),_coord(x, y), _size(lenght, height)
{
}

MenuItem::MenuItem(Entity type, int id, std::string text, ui x, ui y, ui lenght, ui height, std::string texture, bool textureState)
	: _stateTexture(textureState), _texture(texture), _type(type), _id(id), _text(text),_coord(x, y), _size(lenght, height)
{
}

void MenuItem::setCoord(unsigned int x, unsigned int y)
{
    _coord = std::make_pair(x, y);
}

void MenuItem::setSize(unsigned int x, unsigned int y)
{
    _size = std::make_pair(x, y);
}
