/*
** EPITECH PROJECT, 2018
** Player
** File description:
** player
*/

#include "Player.hpp"

Player::Player(float x, float y, unsigned int id, int nb)
	: _number(nb), _speed(0.0f), _bombs(2), _pow(3),
	_superB(false), _kick(false), _shields(0)
{
	_x = x;
	_y = y;
	_id = id;
	_alive = true;
	_type = Entity::PLAYER;
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

bool	Player::hasShield() const
{
	return (_shields > 0);
}

int	Player::getShield() const
{
	return (_shields);
}

void	Player::addShield()
{
	if (_shields < 2)
		_shields += 1;
}

void	Player::rmShield()
{
	if (_shields)
		_shields -= 1;
}

float	Player::getSpeed() const
{
	return (_speed);
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

bool	Player::hasKick() const
{
	return (_kick);
}

pairUC	Player::getPos() const
{
	return std::make_pair(_x, _y);
}

int	Player::getPower() const
{
	return _pow;
}

void	Player::addSpeed()
{
	if (_speed < 0.2)
		_speed += 0.01;
}

bool	Player::getSuper() const
{
	return (_superB);
}

void	Player::addPower()
{
	_pow += 1;
}

void	Player::setSuper(bool tmp)
{
	_superB = tmp;
}

void	Player::setKick(bool tmp)
{
	_kick = tmp;
}

void	Player::pickupItem(std::unique_ptr<IEntity> &item)
{
	eItem	tmp = static_cast<Item *>(item.get())->getItemType();

	if (tmp == eItem::BOMB_UP)
		this->addBomb();
	else if (tmp == eItem::POWER_UP)
		this->addPower();
	else if (tmp == eItem::SPEED)
		this->addSpeed();
	else if (tmp == eItem::SUPER_BOMB)
		this->setSuper(true);
	else if (tmp == eItem::WALL_PASS)
		std::cout << "Picked up Wall pass" << std::endl;
	else if (tmp == eItem::KICK) {
		this->setKick(true);
		std::cout << "Picked up Kick" << std::endl;
	}
}

void Player::setRotation(float rotation)
{
	_rotation = rotation;
}

void Player::ia()
{
}

int Player::getNumber() const
{
	return _number;
}

void Player::setNumber(int nb)
{
	_number = nb;
}