//
// EPITECH PROJECT, 2018
// Teleporter.hpp
// File description:
// header
//

#ifndef TELEPORTER_HPP_
# define TELEPORTER_HPP_

# include <algorithm>
# include <string>
# include <vector>
# include "Item.hpp"

class Teleporter : public Item {
public:
	Teleporter(float, float, int);
	~Teleporter() {};
	int getId() const { return _id; }
	Entity getType() const { return Entity::TELEPORTER; }
	pairUC getPos() const { return _pos; }
	std::string getTexture() const { return "./media/tp.png"; };
	std::string getObj() const { return "./media/tp.obj"; };
	pairUC link() const { return _link; }
	void putPlayer(int playerId) { _players.push_back(playerId); }
	void removePlayer(int playerId) { _players.erase(std::remove(_players.begin(), _players.end(), playerId), _players.end()); };

private:
	pairUC _link;
	pairUC _pos;
	int _id;
	std::vector<int> _players;
};

#endif /* !TELEPORTER_HPP_ */
