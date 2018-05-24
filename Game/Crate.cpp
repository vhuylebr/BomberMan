/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** Crate cpp
*/

#include <iostream>
#include "Crate.hpp"

Crate::Crate(float x, float y, int id)
	: ACube(x, y, "./media/crate.jpg", id)
{
	_isAlive = true;
}

void 	Crate::poke()
{
	std::cout << "Crate here, pos " << _pos.x << ":" << _pos.y << std::endl;
}
