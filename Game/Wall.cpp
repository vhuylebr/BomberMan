/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** Wall cpp
*/

#include <iostream>
#include "Wall.hpp"

Wall::Wall(size_t x, size_t y)
	:_pos{x, y}
{
}

void 	Wall::poke()
{
	std::cout << "Wall here, pos " << _pos.x << ":" << _pos.y << std::endl;
}

bool 	Wall::isAlive() const
{
	return (true);
}

std::pair<std::size_t, std::size_t>	Wall::getPos() const
{
	return std::make_pair(_pos.x, _pos.y);
}

Entity	Wall::getType() const
{
	return Entity::WALL;
}