/*
** EPITECH PROJECT, 2018
** Indie Studio
** File description:
** Bomb implementation
*/

#include <random>
#include <chrono>
#include "Bomb.hpp"

Bomb::Bomb(float x, float y, unsigned int id, std::size_t owner)
	:_counter(100),_owner(owner), _pow(1), _superB(false), _flametime(10), _direction{0, 0}, _momentum(0)
{
	_alive = true;
	_x = x;
	_y = y;
	_id = id;
	_dirs.push_back(std::make_pair(1, 0));
	_dirs.push_back(std::make_pair(0, 1));
	_dirs.push_back(std::make_pair(-1, 0));
	_dirs.push_back(std::make_pair(0, -1));
	_type = Entity::SPHERE;
	_texture = "./media/bomb.png";
	_subtype = SphereSubType::SUBBOMB;
	_scale = 0.1f;
}

Bomb::~Bomb()
{
}

void	Bomb::setSuper(bool tmp)
{
	_superB = tmp;
}

void	Bomb::setPower(int pow)
{
	_pow = pow;
}

std::vector<Fire>	&Bomb::getFlames()
{
	return (_flames);
}

void	Bomb::detonate()
{
	_counter = 2;
}

void	Bomb::tick(unsigned int &id, std::vector<std::vector<std::unique_ptr<EntityPos>>> &map,
			std::vector<std::pair<int, Entity> > &entitiesToRemove, std::vector<eItem> params, std::pair<float, float> posPlayer)
{
	_counter -= 1;
	if (_counter == 0) {
		for (auto &a : _dirs) {
			for (auto i = 1 ; i < _pow ; i += 1) {
				std::pair<std::size_t, std::size_t> tmp(std::ceil(_x) + a.first * i, std::ceil(_y) + a.second * i);
				if (tmp.first > 0 && tmp.second > 0 && tmp.second < map.size() && tmp.first < map[tmp.second].size()) {
					if (map[tmp.second][tmp.first]->isEmpty() || (map[tmp.second][tmp.first]->getType() == Entity::CUBE &&
							map[tmp.second][tmp.first]->getSubType() == ItemStatic::CRATE)) {
						if (tmp.first > posPlayer.first - 14 && tmp.first < posPlayer.first + 14 &&
								tmp.second > posPlayer.second - 14 && tmp.second < posPlayer.second + 14) {
							Fire	add(tmp.first, tmp.second, id);
							add.setAlive(true);
							_flames.push_back(add);
							id += 1;
						}
						if (!map[tmp.second][tmp.first]->isEmpty()) {
							entitiesToRemove.push_back(std::make_pair<int, Entity>(map[tmp.second][tmp.first]->getId(),
							map[tmp.second][tmp.first]->getType()));
							map[tmp.second][tmp.first]->removeFirstEntity();
							std::random_device re;
							std::uniform_int_distribution<int> distrib{1, 100};
							if (distrib(re) < 50)
								map[tmp.second][tmp.first]->addEntity(static_cast<float>(tmp.first), static_cast<float>(tmp.second), id, params);
							if (!_superB)
								break;
						}
					} else if (!map[tmp.second][tmp.first]->isEmpty() && map[tmp.second][tmp.first]->getEntity()->getType() == Entity::CUBE)
						break;
				}
			}
		}
		Fire	add(ceil(_x), ceil(_y), _id);
		_flames.push_back(add);
	} else if (_counter == _flametime * -1) {
		for (auto &a : _flames)
			entitiesToRemove.push_back(std::make_pair<int, Entity>(a.getId(), Entity::CUBE));
		_flames.clear();
	}
}


void	Bomb::tick(unsigned int &id, std::vector<std::vector<std::unique_ptr<EntityPos>>> &map,
			std::vector<std::pair<int, Entity> > &entitiesToRemove, std::vector<eItem> params)
{
	_counter -= 1;
	if (_counter == 0) {
		for (auto &a : _dirs) {
			for (auto i = 1 ; i < _pow ; i += 1) {
				std::pair<std::size_t, std::size_t> tmp(std::ceil(_x) + a.first * i, std::ceil(_y) + a.second * i);
				if (tmp.first > 0 && tmp.second > 0 && tmp.second < map.size() && tmp.first < map[tmp.second].size()) {
					if (map[tmp.second][tmp.first]->isEmpty() || (map[tmp.second][tmp.first]->getType() == Entity::CUBE &&
							map[tmp.second][tmp.first]->getSubType() == ItemStatic::CRATE)) {
						Fire	add(tmp.first, tmp.second, id);
						add.setAlive(true);
						_flames.push_back(add);
						id += 1;
						if (!map[tmp.second][tmp.first]->isEmpty()) {
							entitiesToRemove.push_back(std::make_pair<int, Entity>(map[tmp.second][tmp.first]->getId(),
							map[tmp.second][tmp.first]->getType()));
							map[tmp.second][tmp.first]->removeFirstEntity();
							std::random_device re;
							std::uniform_int_distribution<int> distrib{1, 100};
							if (distrib(re) < 50)
								map[tmp.second][tmp.first]->addEntity(static_cast<float>(tmp.first), static_cast<float>(tmp.second), id, params);
							if (!_superB)
								break;
						}
					} else if (!map[tmp.second][tmp.first]->isEmpty() && map[tmp.second][tmp.first]->getEntity()->getType() == Entity::CUBE)
						break;
				}
			}
		}
		Fire	add(ceil(_x), ceil(_y), _id);
		_flames.push_back(add);
	} else if (_counter == _flametime * -1) {
		for (auto &a : _flames)
			entitiesToRemove.push_back(std::make_pair<int, Entity>(a.getId(), Entity::CUBE));
		_flames.clear();
	}
}

bool 	Bomb::isAlive() const
{
	return (_counter > 0);
}

bool    Bomb::isExplode() const
{
	return (_counter == 0);
}

bool	Bomb::isPushed() const
{
	return (_direction.x || _direction.y);
}

void	Bomb::move()
{
	_x += _direction.x / 15.0f + 1.4f * _momentum * _direction.x;
	_y += _direction.y / 15.0f + 1.4f * _momentum * _direction.y;
}

pairUC	Bomb::getNextPos()
{
	return (std::make_pair<float, float>(std::round(_x + 0.6 * _direction.x), std::round(_y + 0.6 * _direction.y)));
}

void	Bomb::takeDir(pairUC playerPos, float power)
{
	_direction = {playerPos.first, playerPos.second};
	_momentum = power;
}

bool	Bomb::isOutFire() const
{
	return (_counter == _flametime * -1);
}

void	Bomb::collide(Bomb &oth)
{
	if (oth.getMomentum() == 0) {
		oth.takeDir(getDir(), getMomentum());
	}
	takeDir({0, 0}, 0);
}

bool	Bomb::isOver() const
{
	return (_counter < _flametime * -1);
}

std::size_t	Bomb::getOwner()
{
	return (_owner);
}

pairUC	Bomb::getDir() const
{
	return (std::make_pair(_direction.x, _direction.y));
}

float	Bomb::getMomentum() const
{
	return (_momentum);
}

void 	Bomb::setAlive(bool state)
{
	_alive = state;
}