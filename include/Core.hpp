#ifndef CORE_HPP_
# define CORE_HPP_

#include "State.hpp"
#include "Actions.hpp"
#include "IrrLib.hpp"

class Core {
public:
    Core();
    ~Core() = default;

    int run();
private:
    STATE   _state;
    Game    _game;
    Menu    _menu;
    IrrLib  _lib;
    Lobby   _lobby;
};

#endif /* CORE_HPP_ */