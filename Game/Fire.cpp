/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** Fire cpp
*/

#include <iostream>
#include "Fire.hpp"

Fire::Fire(float x, float y, int id)
	: ACube(x, y, "./media/fire.jpg", id, true)
{
}