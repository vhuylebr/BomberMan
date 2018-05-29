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
	std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int> distrib{0, 2};
	_bonusType = static_cast<eItem>(distrib(re));
	std::cout << "Created Item :" << _bonusType << std::endl;
	_id = id;
}

Item::~Item()
{
}


eItem Item::getItemType() const
{
	return (_bonusType);
}
