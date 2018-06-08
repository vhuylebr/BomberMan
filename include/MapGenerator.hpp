/*
** EPITECH PROJECT, 2018
** Indie
** File description:
** Map generator
*/

#ifndef MAPGENERATOR_HPP_
# define MAPGENERATOR_HPP_
# include <vector>
# include <random>
# include <chrono>
# include <iostream>

struct t_coord {
	int x;
	int y;
};

class MapGenerator {
public:
	MapGenerator(int x, int y);
	~MapGenerator();

	void 							generateEmptyMap();
	void 							putPlayer(const int l, const int h, std::vector<char> &) noexcept;
	void 							dispMap() const noexcept;
	void 							fillMap();
	void 							generateMap();
	std::vector<std::vector<char>>	getMap() const { return _map; }
	void 							generatePlayers(const int nbPlayers, const int nbIA);

private:
	void 							putBorders() noexcept;
	void 							putWall(const int, const int);
	bool 							checkCase(const int l, const int h);

	std::vector<std::vector<char>> 	_map;
	int 							_x;
	int 							_y;
};

#endif /* !MAPGENERATOR_HPP_ */