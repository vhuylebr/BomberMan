/*
** EPITECH PROJECT, 2018
** Indie Studio
** File description:
** Bomb header
*/

#ifndef BOMB_HPP_
# define BOMB_HPP_

# include "AEntity.hpp"
# include "Player.hpp"

class Bomb : public AEntity {
public:
    Bomb(float x, float y, unsigned int id, std::size_t);
    ~Bomb();
    // void hit();
    // struct s_bomb extractInfo();
    // void insertInfo();
    Entity getType() const;
    bool   isAlive() const;
    void   tick();
    std::size_t getOwner();
    // int getStartingTime() const;

private:
    int _counter;
    std::size_t _owner;
    // Direction _direction;
};

#endif /* !BOMB_HPP_ */
