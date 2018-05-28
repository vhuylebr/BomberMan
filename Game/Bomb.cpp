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
	:_counter(100),_owner(owner), _pow(1), _flametime(10)
{
	_alive = true;
	_x = x;
	_y = y;
	_id = id;
	_dirs.push_back(std::make_pair(1, 0));
	_dirs.push_back(std::make_pair(0, 1));
	_dirs.push_back(std::make_pair(-1, 0));
	_dirs.push_back(std::make_pair(0, -1));
}

Bomb::~Bomb()
{
}

Entity	Bomb::getType() const
{
    return (Entity::SPHERE);
}

void	Bomb::setPower(int pow)
{
	_pow = pow;
}

std::vector<Fire>	&Bomb::getFlames()
{
	return (_flames);
}

void	Bomb::tick(unsigned int &id, std::vector<std::vector<std::unique_ptr<EntityPos>>> &map, std::vector<std::pair<int, Entity> > &entitiesToRemove,
			std::vector<std::unique_ptr<IEntity>> &_updateEntities)
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
						id += 1;
						add.setAlive(true);
						_flames.push_back(add);
						if (!map[tmp.second][tmp.first]->isEmpty()) {
							entitiesToRemove.push_back(std::make_pair<int, Entity>(map[tmp.second][tmp.first]->getId(),
							map[tmp.second][tmp.first]->getType()));
							map[tmp.second][tmp.first]->removeFirstEntity();
							std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());
							std::uniform_int_distribution<int> distrib{1, 10};
							if (distrib(re) < 6) {
								map[tmp.second][tmp.first]->addEntity(static_cast<float>(tmp.first), static_cast<float>(tmp.second), id);
								_updateEntities.push_back(std::unique_ptr<IEntity>(map[tmp.second][tmp.first]->getEntity().get()));
							}
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
			a.setAlive(false);
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

bool	Bomb::isOutFire() const
{
	return (_counter == _flametime * -1);
}

bool	Bomb::isOver() const
{
	return (_counter < _flametime * -1);
}

std::size_t	Bomb::getOwner()
{
	return (_owner);
}