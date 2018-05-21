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
#include <memory>
#include <utility>
#include "Item.hpp"
#include "Actions.hpp"
#include "IEntity.hpp"
#include "Wall.hpp"
#include "Crate.hpp"
#include "Player.hpp"
#include "Bomb.hpp"

class GameCore {
	public:
		GameCore();
		~GameCore();

		std::vector<std::unique_ptr<IEntity>>	&calc(Actions);
		std::vector<std::unique_ptr<IEntity>>	&getEntities();
		void	init(std::pair<std::size_t, std::size_t>);
		void	init(const std::string &);
		std::pair<std::size_t, std::size_t>	getSize() const;

	private:
		std::vector<std::unique_ptr<IEntity>>	_entities;
		coords				_size;
		Player *_player1;
		std::vector<std::unique_ptr<IEntity>>	_updateEntities;
};

#endif /* !GAMECORE_HPP_ */
