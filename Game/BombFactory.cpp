/*
** EPITECH PROJECT, 2018
** Bomberman
** File description:
** BombFactory
*/

#include "BombFactory.hpp"

BombFactory::BombFactory()
{
	loadNb(100);
}

void	BombFactory::loadNb(std::size_t nb, std::size_t &id)
{
	while (nb) {
		_pool.push_back(std::unique_ptr<Bomb>(new Bomb(-1, -1, id++)));
		nb -= 1;
	}
}

BombFactory::~BombFactory()
{
}

std::unique_ptr<Bomb>	BombFactory::getBomb()
{
	if (_pool.size() == 0)
		loadNb(50);
	return ((_pool.pop_back()).release());
}