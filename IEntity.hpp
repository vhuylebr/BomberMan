/*
** EPITECH PROJECT, 2018
** Indie Studio
** File description:
** Entity Interface 
*/

#ifndef IENTITY_HPP_
	#define IENTITY_HPP_

class IEntity {
public:
    virtual ~IEntity() = default;
    bool isSuperpoz() const = 0;
    void hit() = 0;
    void poke() = 0;
    bool isDestruct() = 0;
    void extractInfo() = 0;
    void insertInfo() = 0;
    Entity getType() = 0;

    enum Entity {
        Box,
        Wall,
        Bomb,
        Player,
        Item
    };
};

#endif /* !IENTITY_HPP_ */
