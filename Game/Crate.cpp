/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** Crate cpp
*/

#include <iostream>
#include "Crate.hpp"

Crate::Crate(float x, float y, int id)
	: ACube(x, y, "./media/crate.jpg", id, false)
{
	_isAlive = true;
}
