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
	_texture = "./media/shield.jpg";
	_subtype = SphereSubType::SUBSHIELD;
	_scale = 0.15f;
}

Shield::~Shield()
{
}

void	Shield::setAlive(bool tmp)
{
	_alive = tmp;
}