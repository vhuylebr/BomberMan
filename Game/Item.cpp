/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** Item class 
*/

#include <random>
#include <chrono>
#include <iostream>
#include <algorithm>
#include "Item.hpp"

Item::Item(float x, float y, unsigned int id, std::vector<eItem> &disp)
	:_x(x), _y(y), _id(id), _alive(false)
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
	_getModel[KICK] = "./media/Shoes.obj";
	_getTexture[KICK] = "./media/Shoes.png";
	_getScale[KICK] = 0.1f;
	_getModel[SHIELD] = "./media/Fireball.obj";
	_getTexture[SHIELD] = "./media/shield.jpg";
	_getScale[SHIELD] = 1.0f;
	loadType(disp);
	_id = id;
}

void	Item::loadType(std::vector<eItem> &disp)
{
	std::random_device re;
	std::uniform_int_distribution<int> distrib{0, 99};
	if (std::find(disp.begin(), disp.end(), eItem::BOMB_UP) != disp.end())
		disp.push_back(eItem::BOMB_UP);
	if (std::find(disp.begin(), disp.end(), eItem::SPEED) != disp.end())
		disp.push_back(eItem::SPEED);
	if (std::find(disp.begin(), disp.end(), eItem::POWER_UP) != disp.end())
		disp.push_back(eItem::POWER_UP);
	int idx = (int)(distrib(re) / 100.0f * (double)disp.size());
	_bonusType = disp[idx];
	//_bonusType = eItem::SHIELD;
//	if (_bonusType == WALL_PASS)
//		loadType(disp);
	//std::cout << "Got " << _bonusType << "from idx " << idx << " from rd " << nb << std::endl;
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
