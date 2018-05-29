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
# include "Metrics.hpp"

enum class GameState {
	NEWGAME,
	LOADGAME
};

struct  parameters
{
	GameState state;                // State si la map doit être à nouveau ou doit être chargée depuis un fichier
	std::wstring gameName;          // Le fichier dans lequel on devra sauvegarde ou get les infos de la map
	int nbPlayers;
	int nbBots;
	std::pair<int,int> mapSize;
	std::vector<eItem> bonuses;		// Vecteur de bonus actifs
	std::string mapname;
	bool split;
};

class GameCore {
public:
	GameCore();
	~GameCore();
	std::vector<std::unique_ptr<IEntity>>	&calc(Actions, STATE &);
	std::vector<std::vector<std::unique_ptr<EntityPos> > >	&getEntities();
	void	init(pairUC);
	void	init(parameters);
	void	init(const std::string &);
	pairUC	getSize() const;
	void 	handlePause(Actions actions, STATE &state);
	void	releaseUpdateEntities();
	void	removeAll();
	std::vector<std::unique_ptr<IEntity>> 	&createPause();
	bool 	playerMovement(Actions act);
	std::vector<std::unique_ptr<IEntity>>	&getMobileEntities();
	std::vector<std::pair<int, Entity> >	&getEntitiesToRemove();
	void	movePlayer(std::pair<float, float>, std::pair<int, int>, Player &, float);
	
	bool checkEnd(STATE &);
	std::vector<std::unique_ptr<IEntity>> &handleEnd(Actions actions, STATE &state);

private:
	void	bombManager(Actions &act);

	std::vector<std::unique_ptr<IEntity>>	_entities;
	coords				_size;
	unsigned int			_id;
	Player				_player1;
	Player				_player2;
	std::vector<Bomb>		_bombs;
	bool	thereIsBomb(int x, int y);
	void	initEndScreen();
	std::vector<std::vector<std::unique_ptr<EntityPos> > > _vectorEntities;
	std::vector<std::unique_ptr<IEntity>>	_updateEntities;
	std::vector<std::unique_ptr<IEntity>>	_mobileEntities;
	std::vector<std::unique_ptr<IEntity>>	_pauseitem;
	std::vector<std::unique_ptr<IEntity>>	_endItem;
	std::vector<std::pair<int, Entity> >	_entitiesToRemove;
};

#endif /* !GAMECORE_HPP_ */
