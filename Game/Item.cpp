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
	_getModel[SPEED] = "./media/speed.obj";
	_getTexture[SPEED] = "./media/speed.png";
	_getScale[SPEED] = 0.5f;
	_getModel[POWER_UP] = "./media/Fireball.obj";
	_getTexture[POWER_UP] = "./media/Fireball.png";
	_getScale[POWER_UP] = 1.0f;
	_getModel[BOMB_UP] = "./media/Bomb.md2";
	_getTexture[BOMB_UP] = "./media/bomb.png";
	_getScale[BOMB_UP] = 0.0015f;
	_getModel[SUPER_BOMB] = "./media/megaBomb.obj";
	_getTexture[SUPER_BOMB] = "./media/megaBomb.png";
	_getScale[SUPER_BOMB] = 1.0f;
	std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int> distrib{0, 4};
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

std::string		Item::getModel()
{
	return _getModel[_bonusType];
}

std::string		Item::getTexture()
{
	return _getTexture[_bonusType];
}

float	Item::getScale()
{
	return _getScale[_bonusType];
}
