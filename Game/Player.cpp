/*
** EPITECH PROJECT, 2018
** Player
** File description:
** player
*/

#include "Player.hpp"

Player::Player(float x, float y, unsigned int id, int nb)
	: _number(nb), _speed(0.0f), _maxbombs(2), _bombs(1),
	  _pow(3), _superB(false), _iaDir(std::make_pair(0, 0)), _forceIa(0), _kick(false), _dmg(false), _picked(false)
{
	_x = x;
	_y = y;
	_id = id;
	_alive = true;
	_type = Entity::PLAYER;
}

void	Player::incForceIa()
{
	_forceIa += 1;
	if (_forceIa >= 14)
		_forceIa = 0;
}

void	Player::dropBomb()
{
	_bombs -= 1;
}

void	Player::addBomb()
{
	_bombs += 1;
}

void 	Player::setBombs(int bombs)
{
	_bombs = bombs;
	_maxbombs = bombs;
}

bool	Player::hasShield() const
{
	return (_shields.size() > 0);
}

std::vector<Shield>	&Player::getShields()
{
	return (_shields);
}

void	Player::addShield(unsigned int &id)
{
	if (_shields.size() < 2) {
		_shields.push_back(Shield(_x, _y, id));
		id += 1;
	}
}

int	Player::rmShield()
{
	if (_shields.size()) {
		unsigned int	tmp = _shields.back().getId();
		_shields.pop_back();
		_dmg = 1;
		return (static_cast<int>(tmp));
	}
	return (-1);
}

float	Player::getSpeed() const
{
	return (_speed);
}

void 	Player::setSpeed(float speed)
{
	_speed = speed;
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
	if (!alive)
		_dmg = 1;
}

bool	Player::hasKick() const
{
	return (_kick);
}

pairUC	Player::getPos() const
{
	return std::make_pair(_x, _y);
}

void 	Player::setPower(int pow)
{
	_pow = pow;
}

int	Player::getPower() const
{
	return _pow;
}

bool	Player::wasDamaged()
{
	if (_dmg) {
		_dmg = false;
		return (true);
	}
	return (false);
}

void	Player::addSpeed()
{
	if (_speed < 0.1)
		_speed += 0.01;
}

bool	Player::getSuper() const
{
	return (_superB);
}

void	Player::setPos(float x, float y)
{
	_x = x;
	_y = y;
	for (auto it : _shields)
		it.setPos(x, y);
}

bool	Player::hasPickedUp()
{
	if (_picked) {
		_picked = false;
		return (true);
	}
	return (false);
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

void	Player::pickupItem(std::unique_ptr<IEntity> &item, unsigned int &id, std::vector<std::unique_ptr<IEntity>> &addVec)
{
	eItem	tmp = static_cast<Item *>(item.get())->getItemType();

	if (tmp == eItem::BOMB_UP) {
		_maxbombs += 1;
		this->addBomb();
	}
	else if (tmp == eItem::POWER_UP)
		this->addPower();
	else if (tmp == eItem::SPEED)
		this->addSpeed();
	else if (tmp == eItem::SUPER_BOMB)
		this->setSuper(true);
//	else if (tmp == eItem::WALL_PASS)
//		return ;
	else if (tmp == eItem::KICK)
		this->setKick(true);
	else if (tmp == eItem::SHIELD) {
		this->addShield(id);
		addVec.push_back(std::unique_ptr<IEntity>(new Shield(_shields.back())));
	}
	_picked = true;
}

void Player::setRotation(float rotation)
{
	_rotation = rotation;
}

void	Player::setIa(std::pair<int, int> dir)
{
	_iaDir = dir;
}

int Player::getNumber() const
{
	return _number;
}

void Player::setNumber(int nb)
{
	_number = nb;
}
