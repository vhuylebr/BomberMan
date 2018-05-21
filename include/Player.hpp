/*
** EPITECH PROJECT, 2018
** player
** File description:
** player
*/

#ifndef PLAYER_HPP_
	#define PLAYER_HPP_

#include <iostream>
#include "AEntity.hpp"

class Player : public AEntity {
public:
	Player(float, float, unsigned int);
	~Player() {};
	void 	poke();
	Entity 	getType() const final;
	bool	isAlive() const;
	pairUC getPos() const;
	float getRotation() const {return _rotation;};
	void setRotation(float);
private:
	float _rotation;
};

#endif /* !PLAYER_HPP_ */
