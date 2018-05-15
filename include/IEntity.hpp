/*
** EPITECH PROJECT, 2018
** Indie Studio
** File description:
** Entity Interface 
*/

#ifndef IENTITY_HPP_
# define IENTITY_HPP_

enum class Entity {
    BOX,
    WALL,
    BOMB,
    PLAYER,
    ITEM
};

class IEntity {
public:
    virtual ~IEntity() = default;
    virtual bool isSuperpoz() const = 0;
    virtual void hit() = 0;
    virtual bool isDestruct() = 0;
    virtual void extractInfo() = 0;
    virtual void insertInfo() = 0;
    virtual Entity getType() const = 0;
};

#endif /* !IENTITY_HPP_ */