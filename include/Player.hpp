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

	bool				isAlive() const;
	void				setAlive(bool);
	pairUC				getPos() const;
	int					getPower() const;
	float				getRotation() const {return _rotation;};
	void				setRotation(float);
	void				pickupItem(std::unique_ptr<IEntity> &, unsigned int &id, std::vector<std::unique_ptr<IEntity>> &);
	void				addPower();
	float				getSpeed() const;
	void 				setSpeed(float speed);
	bool				getSuper() const;
	std::pair<int, int>	getIa() const {return _iaDir;};
	void				setIa(std::pair<int, int>);
	bool				hasKick() const;
	void				setSuper(bool);
	void				setPower(int);
	bool				hasShield() const;
	std::vector<Shield>	&getShields();
	void				setPos(float x, float y);
	void				addShield(unsigned int &);
	int					rmShield();
	void				addPow();
	void				addBomb();
	void				addSpeed();
	void 				setBombs(int bombs);
	void				dropBomb();
	int 				getMaxBombs() const { return _maxbombs; }
	int					getBombCount() const;
	void				setNumber(int);
	void				setKick(bool);
	int					getNumber() const;
	bool				isBot() const {return _isBot; };
	bool				wasDamaged();
	bool				hasPickedUp();
	int				getForceIa() const {return _forceIa;};
	void				incForceIa();

private:

	int 				_number;
	float 				_rotation;
	float				_speed;
	int 				_maxbombs;
	int				_bombs;
	int				_pow;
	bool				_superB;
	std::pair<int, int>		_iaDir;
	int				_forceIa;
	bool				_kick;
	bool				_isBot;
	std::vector<Shield>		_shields;
	bool				_dmg;
	bool				_picked;
};

#endif /* !PLAYER_HPP_ */
