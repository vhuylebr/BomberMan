/*
** EPITECH PROJECT, 2018
** posentity
** File description:
** posentity
*/

#include "EntityPos.hpp"

EntityPos::EntityPos(ItemStatic item, float x, float y, int id)
    :_subType(item)
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

int EntityPos::getId() const
{
    return _entities.begin()->get()->getId();
}

ItemStatic EntityPos::getSubType() const
{
    return _subType;
}

void EntityPos::removeFirstEntity()
{
    _entities.clear();
}

std::unique_ptr<IEntity> &EntityPos::getEntity()
{
    std::unique_ptr<IEntity> &tmp = _entities[0];
    return tmp;
}

EntityPos::~EntityPos()
{
}
