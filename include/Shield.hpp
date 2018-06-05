/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** Shield Entity
*/

#ifndef SHIELD_HPP_
# define SHIELD_HPP_

#include "AEntity.hpp"

class	Shield : public AEntity {
public:
	Shield(float x, float y, unsigned int id);
	~Shield();

	bool	isAlive() const;
	void	setAlive(bool);

private:
	bool	_alive;
};

#endif /* SHIELD_HPP_ */