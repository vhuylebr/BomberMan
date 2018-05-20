/*
** EPITECH PROJECT, 2018
** indie_studio
** File description:
** Crate hpp
*/

#ifndef CRATE_HPP_
	#define CRATE_HPP_

# include "IEntity.hpp"

class Crate : public IEntity {
	public:
		Crate(std::size_t, std::size_t);
		~Crate() {};
		void 	poke();
		Entity 	getType() const final;
		bool	isAlive() const;
		std::pair<std::size_t, std::size_t> getPos() const;

	private:
	coords			_pos;
};

#endif /* !CRATE_HPP_ */
