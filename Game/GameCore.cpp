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
    //_entities.push_back(); add Entities
}

void    GameCore::init(const std::string &file)
{
    init(std::make_pair(100, 100));
    std::cout << "Loading " << file << std::endl;
}

std::vector<Entity>    &GameCore::calc(Actions act)
{
    //std::cout << "Space ? " << (act.space ? "Yes" : "No") << std::endl;
    return (_entities);
}