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
# include "InteractivDecor.hpp"

class Teleporter : public InteractivDecor {
public:
	Teleporter(float x, float y, int id) : InteractivDecor(x, y, id) { }
	~Teleporter() {};
	INTERACTIVDECOR getSubType() const { return INTERACTIVDECOR::TELEPORTER; }
	std::string getTexture() const override { return "./media/tp.obj"; }
	pairUC link() const { return _link; }
	void putPlayer(int playerId) { _players.push_back(playerId); }
	void removePlayer(int playerId) { _players.erase(std::remove(_players.begin(), _players.end(), playerId), _players.end()); };

private:
	pairUC _link;
//	pairUC _pos;
//	int _id;
	std::vector<int> _players;
};

#endif /* !TELEPORTER_HPP_ */
