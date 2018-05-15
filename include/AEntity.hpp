/*
** EPITECH PROJECT, 2018
** Indie studio
** File description:
** header of abstract entity
*/

#ifndef AENTITY_HPP_
# define AENTITY_HPP_

# include "IEntity.hpp"

class AEntity : public IEntity {
public:
    ~AEntity() {}
    bool isAlive() const override { return _alive; }
    int getX() const { return _x; }
    int getY() const { return _y; }
private:
    bool _alive;
    int _x;
    int _y;
};

#endif /* !AENTITY_HPP_ */
