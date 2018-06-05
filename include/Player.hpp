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
#include "Shield.hpp"

class Player : public AEntity {
public:
	Player(float, float, unsigned int, int nb = 2);
	~Player() {};
	void	poke();
	bool	isAlive() const;
	void	setAlive(bool);
	pairUC	getPos() const;
	int	getPower() const;
	float	getRotation() const {return _rotation;};
	void	setRotation(float);
	void	pickupItem(std::unique_ptr<IEntity> &, unsigned int &id, std::vector<std::unique_ptr<IEntity>> &);
	void	addPower();
	float	getSpeed() const;
	bool	getSuper() const;
	bool	hasKick() const;
	void	setSuper(bool);
	bool	hasShield() const;
	std::vector<Shield>	&getShields();
	void	setPos(float x, float y);
	void	addShield(unsigned int &);
	int	rmShield();
	void	addPow();
	void	addBomb();
	void	addSpeed();
	void	dropBomb();
	int	getBombCount() const;
	void	ia();
	void	setNumber(int);
	void	setKick(bool);
	int	getNumber() const;
	bool	isBot() const {return _isBot; };

private:

	int 	_number;
	float 	_rotation;
	float	_speed;
	int	_bombs;
	int	_pow;
	bool	_superB;
	bool	_kick;
	bool	_isBot;
	std::vector<Shield>	_shields;
};

#endif /* !PLAYER_HPP_ */
