/*
** EPITECH PROJECT, 2018
** game
** File description:
** game
*/

#include "GameCore.hpp"

GameCore::GameCore()
{
}

GameCore::~GameCore()
{
}

void    GameCore::init(std::pair<std::size_t, std::size_t> size)
{
    std::cout << "Initializing new game" << std::endl;
    _size.x = size.first;
    _size.y = size.second;
    /*for (auto i = 0 ; i < _size.x ; i += 1) {
        //_entities.push_back(new Wall(i, 0));
        //_entities.push_back(new Wall(i, _size.y - 1));
    }
    for (auto i = 0 ; i < _size.y ; i += 1) {
        //_etities.push_back(new Wall(0, i));
        //_entities.push_back(new Wall(_size.x - 1, i));
    }*/
}

void    GameCore::init(const std::string &file)
{
    init(std::make_pair(100, 100));
    std::cout << "Loading " << file << std::endl;
}

std::vector<Entity>    &GameCore::calc(Actions act)
{
 //   for (auto &i : _entities) {
        //i.poke(act, _entities);
   // }
    return (_entities);
}