/*
** EPITECH PROJECT, 2018
** ACube
** File description:
** ACube
*/

#include "ACube.hpp"

ACube::ACube(float x, float y, std::string texture, int id)
    : _pos({x, y}), _texture(texture), _id(id)
{
}

ACube::~ACube()
{
}

Entity	ACube::getType() const
{
	return Entity::CUBE;
}

pairUC	ACube::getPos() const
{
	return std::make_pair(_pos.x, _pos.y);
}

std::string ACube::getTexture() const
{
    return _texture;
}