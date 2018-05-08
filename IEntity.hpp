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
    bool isSuperpoz() const = default;
    void hit() = default;
    void poke() = default;
    bool isDestruct() = default;
    void extractInfo() = default;
    void insertInfo() = default;
    Entity getType() = default;

    enum Entity {
        Box,
        Wall,
        Bomb,
        Player,
        Item
    };
};

#endif /* !IENTITY_HPP_ */
