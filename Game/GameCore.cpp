/*
** EPITECH PROJECT, 2018
** game
** File description:
** game
*/

#include "GameCore.hpp"
#include <fstream>
#include <iostream>

GameCore::GameCore()
	:_id(1), _player1(-1, -1, _id)
{
}

void    GameCore::init(pairUC size)
{
	std::string filename = "./media/map1.txt";
	std::ifstream file(filename);
	std::string line;
	std::vector<std::shared_ptr<IEntity>> lineEntity;

	std::cout << "Initializing new game" << std::endl;
	_size.x = size.first;
	_size.y = size.second;
	unsigned int x = 0;
	unsigned int y = 0;
	if (!file.is_open()) {
		std::cout << "Open has failed\n";
	} else {
		std::cout << "Open success\n";
		while (getline(file, line)) {
			lineEntity.clear();
			x = 0;
			for (unsigned int j = 0; line[j] != 0; j++) {
				if (line[j] == '0') {
					std::cout << "y = " << y << std::endl;
					lineEntity.push_back(std::shared_ptr<IEntity>(new Wall(static_cast<float>(x), static_cast<float>(y), _id)));
//					_arrayEntities[y][x].push_back(std::shared_ptr<IEntity>(new Wall(static_cast<float>(x), static_cast<float>(y), _id)));
					_entities.push_back(std::shared_ptr<IEntity>(new Wall(static_cast<float>(x), static_cast<float>(y), _id)));
					_id++;
				} else if (line[j] == '1') {
//					_arrayEntities[y][x].push_back(std::shared_ptr<IEntity>(new Crate(static_cast<float>(x), static_cast<float>(y), _id)));
					_entities.push_back(std::shared_ptr<IEntity>(new Crate(static_cast<float>(x), static_cast<float>(y), _id)));
					_id++;
				} else if (line[j] == '2') {
//					_arrayEntities[y][x].push_back(std::shared_ptr<IEntity>(new Player(static_cast<float>(x), static_cast<float>(y), _id)));
					_player1.setPos(static_cast<float>(x), static_cast<float>(y));
					_entities.push_back(std::shared_ptr<IEntity>(&_player1));
				} else if (line[j] == '3') {
//					_arrayEntities[y][x].push_back(std::shared_ptr<IEntity>(new Bomb(static_cast<float>(x), static_cast<float>(y), _id)));
					_entities.push_back(std::shared_ptr<IEntity>(new Bomb(static_cast<float>(x), static_cast<float>(y), _id)));
					_id++;
				}
				x += 1;
			}
			y += 1;
		}
	}
}

GameCore::~GameCore()
{
	if (_updateEntities.size() > 0)
		releaseUpdateEntities();
	_entities.clear();
}

pairUC	GameCore::getSize() const
{
    return (std::make_pair(_size.x, _size.y));
}

void    GameCore::init(const std::string &file)
{
	init(std::make_pair(100, 100));
	std::cout << "Loading " << file << std::endl;
}

std::vector<std::shared_ptr<IEntity>>	&GameCore::getEntities()
{
	return _entities;
}

void GameCore::releaseUpdateEntities()
{
	_updateEntities.clear();
}

std::vector<std::shared_ptr<IEntity>>    &GameCore::calc(Actions act)
{
	bool changed = false;

	if (_updateEntities.size() > 0)
		releaseUpdateEntities();
	if (act.up == true) {
		_player1.setPos(_player1.getPos().first + 0.1, _player1.getPos().second);
		_player1.setRotation(0.0f);
		changed = true;
	}
	if (act.down == true) {
		_player1.setPos(_player1.getPos().first - 0.1, _player1.getPos().second);
		_player1.setRotation(180.0f);
		changed = true;
	}
	if (act.left == true) {
		_player1.setPos(_player1.getPos().first, _player1.getPos().second + 0.1);
		_player1.setRotation(-90.0f);
		changed = true;
	}
	if (act.right == true) {
		_player1.setPos(_player1.getPos().first, _player1.getPos().second - 0.1);
		_player1.setRotation(90.0f);
		changed = true;
	}
	if (act.space == true) {
		Bomb	tmp(_player1.getPos().first, _player1.getPos().second, _id++);
		_bombs.push_back(tmp);
	}
	for (auto it = _bombs.begin() ; it != _bombs.end() ; ++it) {
		it->tick();
		if (!it->isAlive()) {
			_updateEntities.push_back(std::shared_ptr<IEntity>(&_bombs.back()));
			std::cout << "Boom" << std::endl;
		}
	}
	std::cout << "OUt" << std::endl;
	if (changed)
		_updateEntities.push_back(std::shared_ptr<IEntity>(&_player1));
	return (_updateEntities);
}