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
    unsigned char _power;
    bool _superBomb;
    bool _portable;
};

#endif /* !BOMB_HPP_ */
