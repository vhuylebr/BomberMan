#ifndef BOX_HPP_
# define BOX_HPP_

#include "IEntity.hpp"

class   Box {
public:
    Box();
    ~Box();

    bool isSuperpoz() const;
    void hit();
    void poke();
    bool isDestruct();
    void extractInfo();
    void insertInfo();
    IEntity::Entity getType();

    private:
};

#endif /* BOX HPP */