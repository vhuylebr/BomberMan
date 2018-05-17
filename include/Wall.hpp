/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** Wall hpp
*/

#ifndef WALL_HPP_
	#define WALL_HPP_

struct coords {
	std::size_t	x;
	std::size_t	y;
};

# include "IEntity.hpp"

class Wall : public IEntity {
	public:
		Wall();
		~Wall();
		bool 	isSuperpoz() const final;
		void 	hit() final;
		void 	poke();
		bool 	isDestruct() final;
		// void	extractInfo() final;
		// void 	insertInfo() final;
		Entity 	getType() const final;

	private:
	coords			_pos;
};

#endif /* !WALL_HPP_ */
