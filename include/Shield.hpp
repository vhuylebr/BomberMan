/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** Shield Entity
*/

#ifndef SHIELD_HPP_
# define SHIELD_HPP_

#include "ASphere.hpp"

class	Shield : public ASphere {
public:
	Shield(float x, float y, unsigned int id);
	~Shield();

	int 			getId() const { return (_id); }
	void			setPos(float x, float y) {_x = x; _y = y;}
	pairUC 			getPos() const {return (std::pair<float, float>(_x, _y)); }
	void			setAlive(bool);
	bool 			isAlive() const { return (_alive); }
	SphereSubType 	getSubType() const { return (_subtype); }
};

#endif /* SHIELD_HPP_ */