/*
** EPITECH PROJECT, 2018
** Indie Studio
** File description:
** Bomb header
*/

#ifndef BOMB_HPP_
	#define BOMB_HPP_

class Bomb : public IEntity {
public:
    Bomb();
    ~Bomb();
    virtual ~IEntity() override;
    bool isSuperpoz() const override;
    void hit() override;
    void poke() override;
    bool isDestruct() override;
    void extractInfo() override;
    void insertInfo() override;
    Entity getType() override;
};

#endif /* !BOMB_HPP_ */
