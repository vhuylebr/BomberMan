/*
** EPITECH PROJECT, 2018
** ACube
** File description:
** ACube
*/

#ifndef ACUBE_HPP_
	#define ACUBE_HPP_

#include <string>
#include "IEntity.hpp"

class ACube: public IEntity {
	public:
		ACube(float, float, std::string, int, bool);
		~ACube();
		Entity 		getType() const;
		pairUC 		getPos() const;
		std::string	getTexture() const;
		int 		getId() const { return _id; }
		bool 		isAlive() const;
		bool 		isDestructible() const;
		void 		setAlive(bool);
	protected:
		coords 		_pos;
		std::string _texture;
		int 		_id;
		bool		_isAlive;
		bool		_destructible;
};

#endif /* !ACUBE_HPP_ */
