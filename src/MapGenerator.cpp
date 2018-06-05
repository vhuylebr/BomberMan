/*
** EPITECH PROJECT, 2018
** indie
** File description:
** Map generator implementation
*/

#include "MapGenerator.hpp"

MapGenerator::MapGenerator(int x, int y)
	: _x(x), _y(y)
{
}

MapGenerator::~MapGenerator()
{
}

void MapGenerator::putPlayer(const int l, const int h, std::vector<char> &line) noexcept
{
	int tmp_l = l % 5;
	int tmp_h = h % 5;

	if (l == 0 || h == 0 || l == _x - 1 || h == _y - 1) {
		if (tmp_l == 2 || tmp_h == 2)
			line.push_back('P');
		else if (tmp_l == 1 || tmp_l == 3 || tmp_h == 1 || tmp_h == 3)
			line.push_back(' ');
		else
			line.push_back('1');

	} else
		line.push_back('1');
}

void MapGenerator::dispMap() const noexcept
{
	for (auto &h : _map) {
		for (auto &l : h) {
			std::cout << l;
		}
		std::cout << std::endl;
	}
}

bool MapGenerator::checkCase(const int l, const int h)
{
	char count = 0;

	if (l == 0 || h == 0 || h == _y - 1 || l == _x - 1)
		return false;
	if (_map[h - 1][l] == '0')
		count++;
	if (_map[h][l - 1] == '0')
		count++;
	if (_map[h][l + 1] == '0')
		count++;
	if (_map[h + 1][l] == '0')
		count++;
	if (count >= 2)
		return false;
	return true;
}

void MapGenerator::putWall(const int l, const int h)
{
	std::random_device re;
	std::uniform_int_distribution<int> distrib{0, 4};
	char nb = distrib(re);

	if (checkCase(l, h) && nb < 2 && _map[h][l] != ' ')
		_map[h][l] = '0';
	if (h == 1 || h == _y - 2 || l == 1 || l == _x - 2) {
		std::uniform_int_distribution<int> distrib2{0, 7};
		if ((nb = distrib(re)) == 4)
			_map[h][l] = ' ';
	}
}

void MapGenerator::fillMap()
{
	for (int h = 0; h < _y; h++) {
		for (int l = 0; l < _x; l++) {
			if (_map[h][l] == 'P') {
				if (h == 0)
					_map[h + 1][l] = ' ';
				if (l == 0)
					_map[h][l + 1] = ' ';
				if (h == _y - 1)
					_map[h - 1][l] = ' ';
				if (l == _x -1)
					_map[h][l - 1] = ' ';
			}
			putWall(l, h);
		}
	}
}

void MapGenerator::generateEmptyMap()
{
	std::vector<char> line;

	for (int h = 0; h < _y; h++) {
		line.clear();
		for (int l = 0; l < _x; l++) {
			putPlayer(l, h, line);
		}
		_map.push_back(line);
	}
}

void MapGenerator::generateMap()
{
	generateEmptyMap();
	fillMap();
}

static void putOnMap(int x, int y, char c, std::vector<std::vector<char>> &map)
{
	map[y][x] = c;
}

static void putPlayers(char player, std::vector<std::vector<char>> &map, std::vector<t_coord> &coords)
{
	std::random_device re;
	std::uniform_int_distribution<int> distrib{0, static_cast<int>(coords.size() - 1)};
	int nb = distrib(re);
	t_coord tmp;

	if (coords.size() == 0)
		return;
	tmp = coords[nb];
	putOnMap(tmp.x, tmp.y, player, map);
	coords.erase(coords.begin() + nb);
}

static void clearExcessPlayer(std::vector<std::vector<char>> &map)
{
	for (auto &line : map) {
		for (auto &c : line) {
			if (c == 'P')
				c = ' ';
		}
	}
}

void MapGenerator::putBorders() noexcept
{
	std::vector<char> newLine;

	for (int i = 0; i < _x + 2; i++)
		newLine.push_back('0');
	for (auto &line : _map) {
		line.insert(line.begin(), '0');
		line.push_back('0');
	}
	_map.insert(_map.begin(), newLine);
	_map.push_back(newLine);
}

void MapGenerator::generatePlayers(const int nbPlayers, const int nbIA)
{
	std::vector<t_coord> coords;
	int h = 0;
	int l = 0;

	for (auto &line : _map) {
		l = 0;
		for (auto &c : line) {
			if (c == 'P')
				coords.push_back({l, h});
			l++;
		}
		h++;

	}
	putPlayers('4', _map, coords);
	if (nbPlayers > 1)
		putPlayers('4', _map, coords);
	for (int i = 0; i < nbIA && static_cast<unsigned int>(i) < coords.size(); i++) {
		putPlayers('4', _map, coords);
	}
	clearExcessPlayer(_map);
	putBorders();
}