/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** Crate cpp
*/

#include <iostream>
#include "Crate.hpp"

Crate::Crate(size_t x, size_t y)
	: ACube(x, y, "./media/crate.jpg")
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
