/*
** EPITECH PROJECT, 2018
** Indie Studio
** File description:
** Bomb header
*/

#ifndef BOMB_HPP_
# define BOMB_HPP_

# include "AEntity.hpp"
# include ""

class Bomb : public AEntity {
public:
    Bomb(int x, int y);
    ~Bomb();
    bool isSuperpoz() const override;
    void hit() override;
    bool isDestruct() override;
    struct s_bomb extractInfo();
    void insertInfo();
    IEntity::Entity getType() const override;
    int getStartingTime() const;

private:
//    Timer _timer;
//    Timer _starting_time;
    int _timer;
    int _starting_time;
    char _power;
    bool _penetration;
    bool _portable;
    Direction _direction;
};

#endif /* !BOMB_HPP_ */
