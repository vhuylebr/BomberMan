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
    void    menuManager(STATE &);
    void    lobbyManager(STATE &);
    void    gameManager(STATE &);

    STATE   _state;
    Actions _act;
    char    _host;
    Game    _game;
    Menu    _menu;
    IrrLib  _lib;
    Lobby   _lobby;
};

#endif /* CORE_HPP_ */