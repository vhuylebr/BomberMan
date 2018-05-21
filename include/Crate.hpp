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
		Crate(std::size_t, std::size_t);
		~Crate() {};
		void 	poke();
		bool	isAlive() const;
};

#endif /* !CRATE_HPP_ */
