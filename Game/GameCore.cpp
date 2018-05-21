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

	std::cout << "Initializing new game" << std::endl;
	_size.x = size.first;
	_size.y = size.second;
	unsigned int x1 = 0;
	unsigned int y1 = 0;
	if (!file.is_open()) {
		std::cout << "Open has failed\n";
	} else {
		std::cout << "Open success\n";
		while (getline(file, line)) {
			x1 = 0;
			for (unsigned int j = 0; line[j] != 0; j++) {
				if (line[j] == '0') {
					_entities.push_back(std::unique_ptr<IEntity>(new Wall(static_cast<float>(x1), static_cast<float>(y1), _id)));
					_id++;
				} else if (line[j] == '1') {
					_entities.push_back(std::unique_ptr<IEntity>(new Crate(static_cast<float>(x1), static_cast<float>(y1), _id)));
					_id++;
				} else if (line[j] == '2') {
					_player1.setPos(static_cast<float>(x1), static_cast<float>(y1));
					_entities.push_back(std::unique_ptr<IEntity>(&_player1));
				} else if (line[j] == '3') {
					_entities.push_back(std::unique_ptr<IEntity>(new Bomb(static_cast<float>(x1), static_cast<float>(y1), _id)));
					_id++;
				}
				x1 += 1;
			}
			y1 += 1;
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

std::vector<std::unique_ptr<IEntity>>	&GameCore::getEntities()
{
	return _entities;
}

void GameCore::releaseUpdateEntities()
{
	for (auto &i : _updateEntities) {
		i.release();
	}
	_updateEntities.clear();
}

std::vector<std::unique_ptr<IEntity>>    &GameCore::calc(Actions act)
{
	bool changed = false;

	if (_updateEntities.size() > 0)
		releaseUpdateEntities();
	if (act.up == true) {
		_player1->setCoord(_player1->getPos().first + 0.1, _player1->getPos().second);
		_player1->setRotation(0.0f);
		changed = true;
	}
	if (act.down == true) {
		_player1->setCoord(_player1->getPos().first - 0.1, _player1->getPos().second);
		_player1->setRotation(180.0f);
		changed = true;
	}
	if (act.left == true) {
		_player1->setCoord(_player1->getPos().first, _player1->getPos().second + 0.1);
		_player1->setRotation(-90.0f);
		changed = true;
	}
	if (act.right == true) {
		_player1->setCoord(_player1->getPos().first, _player1->getPos().second - 0.1);
		_player1->setRotation(90.0f);
		changed = true;
	}
	if (act.space == true) {
		Bomb	tmp(_player1.getPos().first, _player1.getPos().second, _id++);
		_bombs.push_back(tmp);
	}
	std::cout << "In" << std::endl;
	for (auto it = _bombs.begin() ; it != _bombs.end() ; ++it) {
		std::cout << "In2" << std::endl;
		it->tick();
		if (!it->isAlive()) {
			_updateEntities.push_back(std::unique_ptr<IEntity>(&_bombs.back()));
			std::cout << "Boom" << std::endl;
		}
	}
	std::cout << "OUt" << std::endl;
	if (changed)
		_updateEntities.push_back(std::unique_ptr<IEntity>(&_player1));
	return (_updateEntities);
}