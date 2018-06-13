/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** Item Class 
*/

#ifndef ITEM_HPP_
# define ITEM_HPP_

# include "AEntity.hpp"
# include <string>
# include <map>
# include <vector>
# define NB_ITEMS 6 // Nombre d'items implémentés

enum eItem {
	BOMB_UP,
	POWER_UP,
	SPEED,
	SUPER_BOMB,
	KICK,
	SHIELD,
	BUBG,
	NONE
};

class Item : public IEntity {
public:
	Item(float, float, unsigned int, std::vector<eItem> &);
	~Item();

	eItem		getItemType() const;
	int			getId() const { return _id; }
	void		setPos(float x, float y) { _x = x; _y = y; }
	pairUC		getPos() const { return {_x, _y};}
	bool		isAlive() const { return (_alive);};
	Entity		getType() const {return Entity::ITEM; };
	std::string	getModel();
	std::string	getTexture();
	float		getScale();

private:

	void	loadType(std::vector<eItem> &);

	eItem							_bonusType;
	float							_x;
	float							_y;
	size_t							_id;
	bool							_alive;
	std::map<eItem, std::string>	_getModel;
	std::map<eItem, std::string>	_getTexture;
	std::map<eItem, float>			_getScale;
};

#endif /* !ITEM_HPP_ */
