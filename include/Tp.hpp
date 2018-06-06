//
// EPITECH PROJECT, 2018
// Tp.hpp
// File description:
// header
//

#ifndef TP_HPP_
	#define TP_HPP_

# include <algorithm>
# include <string>
# include <vector>
# include "Item.hpp"

class Tp : public Item {
public:
	Tp(float, float, int);
	~Tp() {};
	int getId() const { return _id; }
	Entity getType() const { return Entity::TELEPORTER; }
	pairUC getPos() const { return _pos; }
	std::string Tp::Tp::getTexture() const { return "./media/tp.png"; };
	std::string Tp::Tp::getObj() const { return "./media/tp.obj"; };
	pairUC link() const { return _link; }
	void putPlayer(int playerId) { _players.push_back(PlayerId); }
	void removePlayer(int playerId) { _players.erase(std::remove(_players.begin(), _players.end(), playerID), _players.end()); };

private:
	pairUC _link;
	pairUC _pos;
	int _id;
	std::vector<int> _players;
};

#endif /* !CRATE_HPP_ */
