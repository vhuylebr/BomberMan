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
		ACube(float, float, std::string);
		~ACube();
		Entity getType() const;
    	pairUC getPos() const;
		std::string getTexture() const;
	protected:
		coords _pos;
		std::string _texture;
};

#endif /* !ACUBE_HPP_ */
