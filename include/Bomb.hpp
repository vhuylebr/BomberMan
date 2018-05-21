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
    Entity getType() const;
    bool   isAlive() const;
    void   tick();
    // int getStartingTime() const;

private:
    int _counter;
    char _power;
    bool _penetration;
    bool _portable;
    coords _pos;
    // Direction _direction;
};

#endif /* !BOMB_HPP_ */
