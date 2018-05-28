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

# define NB_ITEMS 6 // Nombre d'items implémentés

enum eItem {
	BOMB_UP,
	POWER_UP,
	SPEED,
	SUPER_BOMB,
	WALL_PASS,
	KICK,
	NONE
};

class Item : public IEntity {
public:
	Item(float, float, unsigned int);
	~Item();

	eItem	getItemType() const;
	int	getId() const { return _id; }
	void	setPos(float x, float y) { _x = x; _y = y; }
	pairUC	getPos() const { return {_x, _y};}
	bool	isAlive() const { return (_alive);};
	Entity	getType() const {return Entity::ITEM;};
	std::string		getModel() const {return "./media/Fireball.obj";};
	std::string		getTexture() const {return "./media/Fireball.png";};

private:

	eItem	_bonusType;
	float	_x;
	float	_y;
	size_t	_id;
	bool	_alive;
};

#endif /* !ITEM_HPP_ */
