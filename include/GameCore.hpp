/*
** EPITECH PROJECT, 2018
** game
** File description:
** game
*/

#ifndef GAMECORE_HPP_
#define GAMECORE_HPP_

#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include "Item.hpp"
#include "Actions.hpp"
#include "IEntity.hpp"
#include "Wall.hpp"

class GameCore {
	public:
		GameCore();
		~GameCore();

		std::vector<Entity>	&calc(Actions);
		void	init(std::pair<std::size_t, std::size_t>);
		void	init(const std::string &);

	private:
		std::vector<Entity>	_entities;
		coords				_size;
};

#endif /* !GAMECORE_HPP_ */
