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
{
}

GameCore::~GameCore()
{
}

void    GameCore::init(std::pair<std::size_t, std::size_t> size)
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
			std::cout << "toto\n";
			x1 = 0;
			for (unsigned int j = 0; line[j] != 0; j++) {
				if (line[j] == '0') {
					_entities.push_back(std::unique_ptr<IEntity>(new Wall(x1, y1)));
				} else if (line[j] == '1') {
					_entities.push_back(std::unique_ptr<IEntity>(new Crate(x1, y1)));
				} else if (line[j] == '2') {
					_entities.push_back(std::unique_ptr<IEntity>(new Player(x1, y1)));
				}
				x1 += 1;
			}
			y1 += 1;
		}
	}
	// std::cout << "Here" << std::endl;
	// for (auto &a : _entities) {
	// 	a->isAlive();
	// }
}

std::pair<std::size_t, std::size_t>	GameCore::getSize() const
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

std::vector<std::unique_ptr<IEntity>>    &GameCore::calc(Actions act)
{
 //   for (auto &i : _entities) {
        //i.poke(act, _entities);
   // }
    return (_entities);
}
