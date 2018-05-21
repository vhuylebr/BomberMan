/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** Item class 
*/

#include "Item.hpp"

Item::Item(float x, float y, unsigned int id)
{
	setCoord(x, y);
	_id = id;
}

Item::~Item()
{
}

bool 	Item::isSuperpoz() const
{
	return true;
}

void 	Item::hit()
{

}

bool 	Item::isDestruct()
{
	return true;
}

// IEntity::Entity	Item::getType() const
// {
// 	return WALL;
// }