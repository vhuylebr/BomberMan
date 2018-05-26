/*
** EPITECH PROJECT, 2018
** Player
** File description:
** player
*/

#include "Player.hpp"

Player::Player(float x, float y, unsigned int id)
	:_bombs(2), _pow(3)
{
	_x = x;
	_y = y;
	_id = id;
	_alive = true;
}

void 	Player::poke()
{
	std::cout << "Player here, pos " << _x << ":" << _y << std::endl;
}

void	Player::dropBomb()
{
	_bombs -= 1;
}

void	Player::addBomb()
{
	_bombs += 1;
}

int	Player::getBombCount() const
{
	return (_bombs);
}

bool 	Player::isAlive() const
{
	return (_alive);
}

void 	Player::setAlive(bool alive)
{
	_alive = alive;
}

pairUC	Player::getPos() const
{
	return std::make_pair(_x, _y);
}

int	Player::getPower() const
{
	return _pow;
}

Entity	Player::getType() const
{
	return Entity::PLAYER;
}

void Player::setRotation(float rotation)
{
	_rotation = rotation;
}
