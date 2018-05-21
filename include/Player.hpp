/*
** EPITECH PROJECT, 2018
** player
** File description:
** player
*/

#ifndef PLAYER_HPP_
	#define PLAYER_HPP_

#include <iostream>
#include "IEntity.hpp"

class Player : public IEntity {
	public:
		Player(float, float);
		~Player() {};
		void 	poke();
		Entity 	getType() const final;
		bool	isAlive() const;
		int	getId() const {return _id;};
		pairUC getPos() const;
		void setPos(float, float);
	protected:
	private:
		coords _pos;
		int _id;
};

#endif /* !PLAYER_HPP_ */
