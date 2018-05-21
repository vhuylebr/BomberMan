/*
** EPITECH PROJECT, 2018
** Indie Studio
** File description:
** Bomb header
*/

#ifndef BOMB_HPP_
# define BOMB_HPP_

# include "AEntity.hpp"

class Bomb : public AEntity {
public:
    Bomb(float x, float y, unsigned int id);
    ~Bomb() {}
    // void hit();
    // struct s_bomb extractInfo();
    // void insertInfo();
	pairUC getPos() const;
    Entity getType() const;
    // int getStartingTime() const;

private:
//    Timer _timer;
//    Timer _starting_time;
    int _timer;
    int _starting_time;
    char _power;
    bool _penetration;
    bool _portable;
    coords _pos;
    // Direction _direction;
};

#endif /* !BOMB_HPP_ */
