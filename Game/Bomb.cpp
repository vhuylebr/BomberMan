/*
** EPITECH PROJECT, 2018
** Indie Studio
** File description:
** Bomb implementation
*/

#include "Bomb.hpp"

Bomb::Bomb(int x, int y)
    : _timer(EXPLOSION_TIME), _power(1), _penetration(false), _portable(false),
     _direction(NONE_DIR), _x(x), _y(y), _alive(true)
{
}

Bomb::~Bomb()
{
}

bool Bomb::isSuperpoz() const
{
    return false;
}

void Bomb::hit()
{
    _alive = false;
}

bool Bomb::isDestruct()
{
    return true;
}

static struct s_bomb makeBombStruct(Bomb *bomb)
{
    struct s_bomb bomb_st;

    bomb_st.timer = bomb->getStartingTime(); // faire opérator int-operator=(Timer &)
    bomb_st.x = bomb->getX();
    bomb_st.y = bomb->getY();
    // bomb_st.direction = bomb->getDirection();
    // bomb_st.power = bomb->getPower();
    // bomb_st.wallpass = bomb->isWallPass();
    // bomb_st.penetration = bomb.isPen();
}


//Timer Bomb::getStartingTime() const
int Bomb::getStartingTime() const
{
    return _starting_time;
}

struct s_bomb Bomb::extractInfo()
{
    return makeBombStruct(this);
}

void Bomb::insertInfo()
{

}

IEntity::Entity Bomb::getType() const
{
    return (BOMB);
}
