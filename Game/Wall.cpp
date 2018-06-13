/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** Wall cpp
*/

#include <iostream>
#include "Wall.hpp"

Wall::Wall(float x, float y, int id)
	: ACube(x, y, "./media/wall.bmp", id, true)
{
	_isAlive = true;
}

void 	Wall::poke()
{
	std::cout << "Wall here, pos " << _pos.x << ":" << _pos.y << std::endl;
}
