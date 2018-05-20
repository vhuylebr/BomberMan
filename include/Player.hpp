/*
** EPITECH PROJECT, 2018
** player
** File description:
** player
*/

#ifndef PLAYER_HPP_
	#define PLAYER_HPP_

#include <iostream>
#include "IEntity.hpp"

class Player : public IEntity {
	public:
		Player(std::size_t, std::size_t);
		~Player() {};
		void 	poke();
		Entity 	getType() const final;
		bool	isAlive() const;
		int	getId() const {return _id;};
		std::pair<std::size_t, std::size_t> getPos() const;
	protected:
	private:
		coords _pos;
		int _id;
};

#endif /* !PLAYER_HPP_ */
