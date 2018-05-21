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
	Crate(float, float, unsigned int);
	~Crate() {};
	void 	poke();
	bool	isAlive() const;
	unsigned int getId() const { return _id; }
private:
	unsigned int _id;
};

#endif /* !CRATE_HPP_ */
