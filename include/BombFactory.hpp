/*
** EPITECH PROJECT, 2018
** Bomberman
** File description:
** BombFactory
*/

#ifndef BOMBFACTORY_HPP_
# define BOMBFACTORY_HPP_

#include <memory>
#include <vector>
#include "Bomb.hpp"

class	BombFactory {
public:
	BombFactory();
	~BombFactory();

	std::unique_ptr<Bomb>				getBomb();
	void								loadNb(std::size_t, std::size_t &);

private:
	std::vector<std::unique_ptr<Bomb>>	_pool;
};

#endif /* !BOMBFACTORY_HPP_ */