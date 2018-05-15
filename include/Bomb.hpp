/*
** EPITECH PROJECT, 2018
** Indie Studio
** File description:
** Bomb header
*/

#ifndef BOMB_HPP_
# define BOMB_HPP_

# include "IEntity.hpp"

class Bomb : public IEntity {
public:
    Bomb();
    ~Bomb();
    bool isSuperpoz() const override;
    void hit() override;
    void poke() override;
    bool isDestruct() override;
    void extractInfo() override;
    void insertInfo() override;
    IEntity::Entity getType() const override;

private:
    unsigned int timer;
    char power;
    bool penetration;
};

#endif /* !BOMB_HPP_ */
