/*
** EPITECH PROJECT, 2018
** ACube
** File description:
** ACube
*/

#include "ACube.hpp"

ACube::ACube(float x, float y, std::string texture, int id, bool d)
    : _pos({x, y}), _texture(texture), _id(id), _destructible(d)
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

bool    ACube::isDestructible() const
{
    return (_destructible);
}

std::string ACube::getTexture() const
{
    return _texture;
}

bool ACube::isAlive() const
{
    return _isAlive;
}

void    ACube::setAlive(bool alive)
{
    _isAlive = alive;
}