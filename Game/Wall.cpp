/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** Wall cpp
*/

#include "Wall.hpp"

Wall::Wall()
{
}

Wall::~Wall()
{
}


bool 	Wall::isSuperpoz() const
{
	return (false);
}

void 	Wall::hit()
{
	
}

void 	Wall::poke()
{

}

bool 	Wall::isDestruct()
{
	return (false);
}

Entity	Wall::getType() const
{
	return Entity::ITEM;
}