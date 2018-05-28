/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** Item class 
*/

#include <random>
#include <chrono>
#include "Item.hpp"

Item::Item(float x, float y, unsigned int id)
	:ACube(x, y, "bonus", id)
{
	std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int> distrib{0, 2};
	_type = static_cast<eItem>(distrib(re));
	_id = id;
}

Item::~Item()
{
}

eItem Item::getItemType() const
{
	return (_type);
}