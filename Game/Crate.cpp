/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** Crate cpp
*/

#include <iostream>
#include "Crate.hpp"

Crate::Crate(size_t x, size_t y)
	:_pos{x, y}
{
}

void 	Crate::poke()
{
	std::cout << "Crate here, pos " << _pos.x << ":" << _pos.y << std::endl;
}

bool 	Crate::isAlive() const
{
	std::cout << "Crate here, pos " << _pos.x << ":" << _pos.y << std::endl;
	return (true);
}

std::pair<std::size_t, std::size_t>	Crate::getPos() const
{
	return std::make_pair(_pos.x, _pos.y);
}

Entity	Crate::getType() const
{
	return Entity::CRATE;
}