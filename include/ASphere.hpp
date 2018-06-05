/*
** EPITECH PROJECT, 2018
** ACube
** File description:
** ASphere
*/

#ifndef ASPHERE_HPP_
 #define ASPHERE_HPP_

#include <string>
#include "IEntity.hpp"

enum 	SphereSubType {
	SUBBOMB,
	SUBSHIELD
};

class ASphere: public IEntity {
public:

	std::string getTexture() const {return (_texture); };
	int getId() const { return (_id); }
	bool isAlive() const { return (_alive); }
	Entity getType() const { return (Entity::SPHERE); }
	SphereSubType getSubType() const { return (_subtype); }
	pairUC getPos() const {return (std::pair<float, float>(_x, _y)); }
	void	setPos(float x, float y) {_x = x; _y = y;}
	float	getX() const { return (_x); }
	float	getY() const { return (_y); }
	float	getScale() const { return (_scale); };
protected:
	bool	_alive;
	float	_x;
	float	_y;
	unsigned int _id;
	Entity	_type;
	std::string	_texture;
	SphereSubType 	_subtype;
	float _scale;
};
#endif /* ASPHERE_HPP_ */