/*
** EPITECH PROJECT, 2018
** Indie Studio
** File description:
** Bomb header
*/

#ifndef BOMB_HPP_
# define BOMB_HPP_

# include <vector>
# include <cmath>
# include "EntityPos.hpp"
# include "AEntity.hpp"
# include "Fire.hpp"
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
    bool   isOutFire() const;
    void   tick(unsigned int &, std::vector<std::vector<std::unique_ptr<EntityPos>>> &);
    bool    isOver() const;
    std::size_t getOwner();
    bool    isExplode() const;
    std::vector<Fire>    &getFlames();
    void	setPower(int pow);
    // int getStartingTime() const;

private:
    int _counter;
    std::size_t _owner;
    int         _pow;
    std::vector<Fire> _flames;
    std::vector<pairUC> _dirs;
    int           _flametime;
    // Direction _direction;
};

#endif /* !BOMB_HPP_ */
