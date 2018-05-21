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
		Wall(std::size_t, std::size_t);
		~Wall() {};
		void 	poke();
		bool	isAlive() const;
};

#endif /* !WALL_HPP_ */
