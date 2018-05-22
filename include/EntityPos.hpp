/*
** EPITECH PROJECT, 2018
** enti
** File description:
** enti
*/

#ifndef ENTITYPOS_HPP_
	#define ENTITYPOS_HPP_

#include <vector>
#include <memory>
#include <functional>
#include <map>
#include "IEntity.hpp"

enum class ItemStatic {
	WALL,
	CRATE
};

using ptrFunc = std::function<std::unique_ptr<IEntity>(float, float, int)>;

template <typename T>
std::unique_ptr<IEntity>	addItem(float x, float y, int id)
{
	return std::make_unique<T>(x, y, id);
}

class EntityPos {
	public:
		EntityPos(ItemStatic, float, float, int);
		EntityPos();
		~EntityPos();
		bool isEmpty() const { return (!_entities.size());};
		// Entity getFirstEntity() const;
		// void addEntity(std::unique_ptr<Entity>&);
	private:
		std::map<ItemStatic, ptrFunc> _functionMap;
		std::vector<std::unique_ptr<IEntity> > _entities;
};

#endif /* !ENTITYPOS_HPP_ */
