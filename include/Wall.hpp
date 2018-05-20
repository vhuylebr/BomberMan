/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** Wall hpp
*/

#ifndef WALL_HPP_
	#define WALL_HPP_

# include "IEntity.hpp"

class Wall : public IEntity {
	public:
		Wall(std::size_t, std::size_t);
		~Wall() {};
		void 	poke();
		Entity 	getType() const final;
		bool	isAlive() const;
		std::pair<std::size_t, std::size_t> getPos() const;

	private:
	coords			_pos;
};

#endif /* !WALL_HPP_ */
