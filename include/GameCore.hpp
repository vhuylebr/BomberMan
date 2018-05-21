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
# include "State.hpp"
# include "BombFactory.hpp"

class GameCore {
public:
	GameCore();
	~GameCore();
	std::vector<std::unique_ptr<IEntity>>	&calc(Actions);
	std::vector<std::unique_ptr<IEntity>>	&getEntities();
	void	init(pairUC);
	void	init(const std::string &);
	pairUC	getSize() const;
	void 	releaseUpdateEntities();
	std::vector<std::unique_ptr<IEntity>> 	&createPause();
	void 	handlePause(Actions actions, STATE &state);


private:
	std::vector<std::unique_ptr<IEntity>>	_entities;
	coords				_size;
	unsigned int _id;
	Player 				_player1;
	std::vector<Bomb>		_bombs;
	//BombFactory			_bfact;
	std::vector<std::unique_ptr<IEntity>>	_updateEntities;
	std::vector<std::unique_ptr<IEntity>>	_pause;
};

#endif /* !GAMECORE_HPP_ */
