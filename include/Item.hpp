/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** Item Class 
*/

#ifndef ITEM_HPP_
	#define ITEM_HPP_

# include "IEntity.hpp"

# define NB_ITEMS 6 // Nombre d'items implémentés

enum class eItem {
	BOMB_UP,
	POWER_UP,
	PENE,
	SPEED,
	WALL_PASS,
	KICK,
	NONE
};

class Item : public IEntity {
public:
	Item();
	~Item();
	bool 	isSuperpoz() const final;
	void 	hit() final;
	void 	poke() final;
	bool 	isDestruct() final;
	// void	extractInfo() final;
	// void 	insertInfo() final;
	IEntity::Entity 	getType() const final;
private:
};

#endif /* !ITEM_HPP_ */
