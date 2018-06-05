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

	void	setAlive(bool);
};

#endif /* SHIELD_HPP_ */