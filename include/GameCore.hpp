/*
** EPITECH PROJECT, 2018
** game
** File description:
** game
*/

#ifndef GAMECORE_HPP_
# define GAMECORE_HPP_

# include <string>
# include <iostream>
# include <vector>
# include <memory>
# include <utility>
# include "Item.hpp"
# include "Actions.hpp"
# include "IEntity.hpp"
# include "Wall.hpp"
# include "Crate.hpp"
# include "Player.hpp"
# include "Bomb.hpp"

class GameCore {
public:
	GameCore() : _id(1) {}
	~GameCore();
	std::vector<std::unique_ptr<IEntity>>	&calc(Actions);
	std::vector<std::unique_ptr<IEntity>>	&getEntities();
	void	init(pairUC);
	void	init(const std::string &);
	pairUC	getSize() const;
	void releaseUpdateEntities();

private:
	std::vector<std::unique_ptr<IEntity>>	_entities;
	coords				_size;
	Player *_player1;
	std::vector<std::unique_ptr<IEntity>>	_updateEntities;
	unsigned int _id;
};

#endif /* !GAMECORE_HPP_ */
