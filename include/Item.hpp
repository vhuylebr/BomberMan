/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** Item Class 
*/

#ifndef ITEM_HPP_
# define ITEM_HPP_

# include "IEntity.hpp"
# include <string>

# define NB_ITEMS 6 // Nombre d'items implémentés

enum class eItem {
	BOMB_UP,
	POWER_UP,
	SUPER_BOMB,
	SPEED,
	WALL_PASS,
	KICK,
	NONE
};

std::string itemToStr(eItem item);

class Item : public IEntity {
public:
	Item();
	~Item();
	// void	extractInfo() final;
	// void 	insertInfo() final;
private:
};

#endif /* !ITEM_HPP_ */
