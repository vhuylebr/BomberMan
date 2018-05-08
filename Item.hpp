/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** Item Class 
*/

#ifndef ITEM_HPP_
	#define ITEM_HPP_

# include "IEntity.hpp"

class Item : public IEntity {
	public:
		Item();
		~Item();
		bool 	isSuperpoz() const final;
		void 	hit() final;
		void 	poke() final;
		bool 	isDestruct() final;
		// void	extractInfo() final;
		// void 	insertInfo() final;
		IEntity::Entity 	getType() const final;

	protected:
	private:
};

#endif /* !ITEM_HPP_ */
