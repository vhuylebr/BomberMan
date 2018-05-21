/*
** EPITECH PROJECT, 2018
** ACube
** File description:
** ACube
*/

#include "ACube.hpp"

ACube::ACube(std::size_t x, std::size_t y, std::string texture)
    : _pos({x, y}), _texture(texture)
{
}

ACube::~ACube()
{
}

Entity	ACube::getType() const
{
	return Entity::CUBE;
}

std::pair<std::size_t, std::size_t>	ACube::getPos() const
{
	return std::make_pair(_pos.x, _pos.y);
}

std::string ACube::getTexture() const
{
    return _texture;
}