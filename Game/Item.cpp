/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** Item class 
*/

#include <random>
#include <chrono>
#include <iostream>
#include "Item.hpp"

Item::Item(float x, float y, unsigned int id)
	: _x(x), _y(y), _id(id), _alive(false)
{
	std::cout << "Created Item " << std::endl;
	std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int> distrib{0, 2};
	_bonusType = static_cast<eItem>(distrib(re));
	_id = id;
}

Item::~Item()
{
}

eItem Item::getItemType() const
{
	return (_bonusType);
}
