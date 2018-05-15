#ifndef CORE_HPP_
# define CORE_HPP_

# include "State.hpp"
# include "Actions.hpp"
# include "IrrLib.hpp"
# include "GameCore.hpp"
# include "Menu.hpp"

class Core {
public:
    Core();
    ~Core() = default;

    int run();
    void menuManager(STATE &last);
    // void lobbyManager(STATE &last);
    // void gameManager(STATE &last);
private:
    STATE   _state;
    GameCore    _game;
    Menu    _menu;
    IrrLib  _lib;
    // Lobby   _lobby;
    Actions _act;
};

#endif /* CORE_HPP_ */
