/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** Fire hpp
*/

#ifndef FIRE_HPP_
	#define FIRE_HPP_

# include "ACube.hpp"

class Fire : public ACube {
public:
	Fire(float, float, int);
	~Fire() {};
	void 	poke();
};

#endif /* !FIRE_HPP_ */
