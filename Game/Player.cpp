/*
** EPITECH PROJECT, 2018
** Player
** File description:
** player
*/

#include "Player.hpp"

Player::Player(size_t x, size_t y)
	:_pos{x, y}
{
}

void 	Player::poke()
{
	std::cout << "Player here, pos " << _pos.x << ":" << _pos.y << std::endl;
}

bool 	Player::isAlive() const
{
	std::cout << "Player here, pos " << _pos.x << ":" << _pos.y << std::endl;
	return (true);
}

std::pair<std::size_t, std::size_t>	Player::getPos() const
{
	return std::make_pair(_pos.x, _pos.y);
}

void Player::setPos(std::size_t x, std::size_t y)
{
	_pos.x = x;
	_pos.y = y;
}

Entity	Player::getType() const
{
	return Entity::PLAYER;
}