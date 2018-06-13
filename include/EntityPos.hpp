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
#include <unordered_map>
#include "Item.hpp"
#include "IEntity.hpp"
#include "Crate.hpp"
#include "Wall.hpp"
#include "Player.hpp"

enum class ItemStatic {
	WALL,
	CRATE,
	PLAYER,
	ITEM
};

typedef std::function<std::unique_ptr<IEntity>(float, float, int)> ptrFunc;

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
		bool 						isEmpty() const { return (!_entities.size());};
		Entity 						getType() const;
		ItemStatic 					getSubType() const;
		int 						getId() const;
		void						stomp();
		std::unique_ptr<IEntity>	&getEntity();
		void 						removeFirstEntity();
		void 						addEntity(float, float, unsigned int &, std::vector<eItem> &);
		void						addWall(float x, float y, unsigned int &id);

	private:
		std::unordered_map<ItemStatic, ptrFunc> _functionMap;
		std::vector<std::unique_ptr<IEntity> > 	_entities;
		ItemStatic 								_subType;
};

#endif /* !ENTITYPOS_HPP_ */
