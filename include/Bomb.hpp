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
    bool   isAlive() const;
    bool   isOutFire() const;
    void   tick(unsigned int &, std::vector<std::vector<std::unique_ptr<EntityPos>>> &,
        std::vector<std::pair<int, Entity> > &, std::vector<std::unique_ptr<IEntity>> &);
    bool    isOver() const;
    std::size_t getOwner();
    bool    isExplode() const;
    std::vector<Fire>   &getFlames();
    void	setPower(int pow);
    void	detonate();
    void    setSuper(bool);

private:
    int _counter;
    std::size_t _owner;
    int         _pow;
    bool        _superB;
    std::vector<Fire> _flames;
    std::vector<pairUC> _dirs;
    int           _flametime;
    // Direction _direction;
};

#endif /* !BOMB_HPP_ */
