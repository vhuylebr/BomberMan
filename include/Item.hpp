/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** Item Class 
*/

#ifndef ITEM_HPP_
# define ITEM_HPP_

# include "ACube.hpp"
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

class Item : public ACube {
public:
	Item(float, float, unsigned int);
	~Item();

	eItem getItemType() const;

private:

	eItem	_type;
};

#endif /* !ITEM_HPP_ */
