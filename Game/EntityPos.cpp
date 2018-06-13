/*
** EPITECH PROJECT, 2018
** posentity
** File description:
** posentity
*/

#include "Item.hpp"
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

void    EntityPos::stomp()
{
    _entities.clear();
}

void    EntityPos::addWall(float x, float y, unsigned int &id)
{

    _entities.push_back(std::make_unique<Wall>(x, y, id));
    id += 1;
}

void EntityPos::addEntity(float x, float y, unsigned int &id, std::vector<eItem> &disp)
{
    _entities.push_back(std::make_unique<Item>(x, y, id, disp));
    id += 1;
}

std::unique_ptr<IEntity> &EntityPos::getEntity()
{
    std::unique_ptr<IEntity> &tmp = _entities[0];
    return tmp;
}

EntityPos::~EntityPos()
{
}
