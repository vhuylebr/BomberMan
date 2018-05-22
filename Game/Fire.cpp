/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** Fire cpp
*/

#include <iostream>
#include "Fire.hpp"

Fire::Fire(float x, float y, int id)
	: ACube(x, y, "./media/fire.jpg", id)
{
}

void 	Fire::poke()
{
	std::cout << "Fire here, pos " << _pos.x << ":" << _pos.y << std::endl;
}

bool 	Fire::isAlive() const
{
	std::cout << "Fire here, pos " << _pos.x << ":" << _pos.y << std::endl;
	return (true);
}
