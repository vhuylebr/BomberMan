/*
** EPITECH PROJECT, 2018
** player
** File description:
** player
*/

#ifndef PLAYER_HPP_
	#define PLAYER_HPP_

#include <memory>
#include <iostream>
#include "Item.hpp"
#include "AEntity.hpp"

class Player : public AEntity {
public:
	Player(float, float, unsigned int);
	~Player() {};
	void	poke();
	bool	isAlive() const;
	void	setAlive(bool);
	pairUC	getPos() const;
	int		getPower() const;
	float	getRotation() const {return _rotation;};
	void	setRotation(float);
	void	pickupItem(std::unique_ptr<IEntity> &);
	void	addPower();
	float	getSpeed() const;
	bool	getSuper() const;
	void	setSuper(bool);

	void	addBomb();
	void	addPow();
	void	addSpeed();
	void	dropBomb();
	int	getBombCount() const;
	void	ia();

private:
	float 	_rotation;
	float	_speed;
	int	_bombs;
	int	_pow;
	bool	_superB;
};

#endif /* !PLAYER_HPP_ */
