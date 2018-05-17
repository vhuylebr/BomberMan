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
};

#endif /* !WALL_HPP_ */
