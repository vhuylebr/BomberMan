/*
** EPITECH PROJECT, 2018
** Indie Studio
** File description:
** Bomb implementation
*/

#include "Bomb.hpp"

Bomb::Bomb(float x, float y, unsigned int id, std::size_t owner)
	:_counter(300), _owner(owner)
{
	_alive = true;
	_x = x;
	_y = y;
	_id = id;
}

Bomb::~Bomb()
{
}

Entity	Bomb::getType() const
{
    return (Entity::SPHERE);
}

void	Bomb::tick()
{
	_counter -= 1;
}

bool 	Bomb::isAlive() const
{
	return (_counter > 0);
}

std::size_t	Bomb::getOwner()
{
	return (_owner);
}