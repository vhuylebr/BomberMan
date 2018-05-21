/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** Wall hpp
*/

#ifndef WALL_HPP_
	#define WALL_HPP_

# include "ACube.hpp"

class Wall : public ACube {
public:
	Wall(float, float, unsigned int);
	~Wall() {};
	void 	poke();
	bool	isAlive() const;
	unsigned int getId() const { return _id; }
private:
	unsigned int _id;
};

#endif /* !WALL_HPP_ */
