/*
** EPITECH PROJECT, 2018
** indie
** File description:
** Map
*/

#ifndef MAP_HPP_
# define MAP_HPP_

#include <string>

struct Map {
	std::string imgFileName;
	std::string mapName;
	std::string fileName;
	unsigned int length;
	unsigned int height;
	unsigned int nbBotsMax;
};

#endif /* !MAP_HPP_ */
