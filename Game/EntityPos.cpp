/*
** EPITECH PROJECT, 2018
** posentity
** File description:
** posentity
*/

#include "EntityPos.hpp"

EntityPos::EntityPos(ItemStatic item, float x, float y, int id)
{
    _functionMap[ItemStatic::CRATE] = addItem<Crate>;
    _functionMap[ItemStatic::WALL] = addItem<Wall>;
    _functionMap[ItemStatic::PLAYER] = addItem<Player>;
    _entities.push_back(_functionMap[item](x, y, id));
}

EntityPos::EntityPos()
{
    _functionMap[ItemStatic::CRATE] = addItem<Crate>;
    _functionMap[ItemStatic::WALL] = addItem<Wall>;
    _functionMap[ItemStatic::PLAYER] = addItem<Player>;
}

Entity EntityPos::getType() const
{
    return _entities.begin()->get()->getType();
}

std::unique_ptr<IEntity> &EntityPos::getEntity()
{
    std::unique_ptr<IEntity> &tmp = _entities[0];
    return tmp;
}

EntityPos::~EntityPos()
{
}
