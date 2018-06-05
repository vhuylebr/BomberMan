/*
** EPITECH PROJECT, 2018
** Indie Studio
** File description:
** Entity Interface 
*/

#ifndef IENTITY_HPP_
# define IENTITY_HPP_

#include <utility>
#include <cstddef>

typedef std::pair<float, float> pairUC;

enum class Entity {
    BOX,
    BOMB,
    PLAYER,
    ITEM,
    BUTTON,
    CHECKBOX,
    INPUT,
    LABEL,
    LISTBOX,
    SPHERE,
    CUBE
};

struct coords {
	float	x;
	float	y;
};


class IEntity {
public:
    virtual ~IEntity() = default;
    virtual int getId() const = 0;
    virtual Entity getType() const = 0;
    virtual pairUC getPos() const = 0;
};

#endif /* !IENTITY_HPP_ */
