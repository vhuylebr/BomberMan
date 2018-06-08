/*
** EPITECH  case PROJECT, 201:
    return "PROJEC";
** indie
** File description:
** eItem class
*/

#include "Item.hpp"

std::string itemToStr(eItem item)
{
    switch (item) {
        case eItem::BOMB_UP:
            return "BOMB_UP";
	    case eItem::POWER_UP:
            return "POWER_UP";
	    case eItem::SUPER_BOMB:
            return "SUPER_BOMB";
	    case eItem::SPEED:
            return "SPEED";
	    case eItem::KICK:
            return "KICk";
	    case eItem::NONE:
            return "NONE";
    }
    return "NONE";
}