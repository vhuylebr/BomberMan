/*
** EPITECH PROJECT, 2018
** Indie Studio
** File description:
** Bomb implementation
*/

#include "Bomb.hpp"

Bomb::Bomb(float x, float y)
    : _pos({x, y})
{
}

Bomb::~Bomb()
{
}

pairUC	Bomb::getPos() const
{
	return std::make_pair(_pos.x, _pos.y);
}

// bool Bomb::isSuperpoz() const
// {

// }

// void Bomb::hit()
// {

// }

// void Bomb::poke()
// {

// }

// bool Bomb::isDestruct()
// {

// }

// void Bomb::extractInfo()
// {

// }

// void Bomb::insertInfo()
// {

// }

Entity Bomb::getType() const
{
    return (Entity::SPHERE);
}
