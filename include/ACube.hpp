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
		ACube(std::size_t, std::size_t, std::string);
		~ACube();
		Entity getType() const;
    	std::pair<std::size_t, std::size_t> getPos() const;
		std::string getTexture() const;
	protected:
		coords _pos;
		std::string _texture;
};

#endif /* !ACUBE_HPP_ */
