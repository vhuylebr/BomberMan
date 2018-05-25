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
# include <fstream>
# include <memory>
# include <utility>
# include <algorithm>
# include <cmath>
# include "Item.hpp"
# include "Actions.hpp"
# include "IEntity.hpp"
# include "Wall.hpp"
# include "Crate.hpp"
# include "Player.hpp"
# include "State.hpp"
# include "BombFactory.hpp"
# include "MenuItem.hpp"
# include "Fire.hpp"
# include "EntityPos.hpp"

class GameCore {
public:
	GameCore();
	~GameCore();
	std::vector<std::unique_ptr<IEntity>>	&calc(Actions);
	std::vector<std::vector<std::unique_ptr<EntityPos> > >	&getEntities();
	void	init(pairUC);
	void	init(const std::string &);
	pairUC	getSize() const;
	void 	handlePause(Actions actions, STATE &state);
	void	releaseUpdateEntities();
	void	removeAll();
	std::vector<std::unique_ptr<IEntity>> 	&createPause();
	bool 	playerMovement(Actions act);
	std::vector<std::unique_ptr<IEntity>>	&getMobileEntities();
	std::vector<std::pair<int, Entity> >	&getEntitiesToRemove();
	

private:
	void	bombManager(Actions &act);

	std::vector<std::unique_ptr<IEntity>>	_entities;
	coords				_size;
	unsigned int			_id;
	Player 				_player1;
	Player 				_player2;
	std::vector<Bomb>		_bombs;
	bool	thereIsBomb(int x, int y);
	std::vector<std::vector<std::unique_ptr<EntityPos> > > _vectorEntities;
	std::vector<std::unique_ptr<IEntity>>	_updateEntities;
	std::vector<std::unique_ptr<IEntity>>	_mobileEntities;
	std::vector<std::unique_ptr<IEntity>>	_pauseitem;
	std::vector<std::pair<int, Entity> >	_entitiesToRemove;
};

#endif /* !GAMECORE_HPP_ */
