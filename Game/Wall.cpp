/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** Wall cpp
*/

#include <iostream>
#include "Wall.hpp"

Wall::Wall(size_t x, size_t y)
	: ACube(x, y, "./media/wall.bmp")
{
}

void 	Wall::poke()
{
	std::cout << "Wall here, pos " << _pos.x << ":" << _pos.y << std::endl;
}

bool 	Wall::isAlive() const
{
	std::cout << "Wall here, pos " << _pos.x << ":" << _pos.y << std::endl;
	return (true);
}
