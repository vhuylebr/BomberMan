/*
** EPITECH PROJECT, 2018
** Indie Studio
** File description:
** Bomb header
*/

#ifndef BOMB_HPP_
# define BOMB_HPP_

# include "AEntity.hpp"

class Bomb : public IEntity {
public:
    Bomb(size_t x, size_t y);
    ~Bomb();
    // bool isSuperpoz() const;
    // void hit();
    // bool isDestruct();
    // struct s_bomb extractInfo();
    // void insertInfo();
	std::pair<std::size_t, std::size_t> getPos() const;
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
