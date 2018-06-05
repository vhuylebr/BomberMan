/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** Shield Entity
*/

#include "Shield.hpp"

Shield::Shield(float x, float y, unsigned int id)
{
	_alive = true;
	_x = x;
	_y = y;
	_id = id;
	_type = Entity::SPHERE;
}

Shield::~Shield()
{
}

void	Shield::setAlive(bool tmp)
{
	_alive = tmp;
}

bool	Shield::isAlive() const
{
	return (_alive);
}
