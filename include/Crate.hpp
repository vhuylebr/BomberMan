/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** Crate hpp
*/

#ifndef CRATE_HPP_
	#define CRATE_HPP_

# include "ACube.hpp"

class Crate : public ACube {
public:
	Crate(float, float, int);
	~Crate() {};
};

#endif /* !CRATE_HPP_ */
