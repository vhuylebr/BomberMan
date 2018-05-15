#include "Core.hpp"

Core::Core()
    :_state(STATE::MENU), _act(), _host(-1), _game(), _menu(), _lib(_act), _lobby()
{
}

void    Core::menuManager(STATE &last)
{
    state = state;
    _lib.getActions();
    _lib.affMenuItem(_menu.getMenu(_act));
}

void    Core::lobbyManager(STATE &last)
{
    //last = state;
}

void    Core::gameManager(STATE &last)
{
    last = last;
    
    if (_host) {
        
    } else {
        
    }
}

int     run()
{
    STATE   lstate = _state;

    while (_state != STATE::EXIT && _lib.getRun()) {
        if (_state == STATE::MENU)
            menuManager(lstate);
        else if (_state == STATE::LOBBY)
            lobbyManager(lstate);
        else if (_state == STATE::GAME)
            gameManager(lstate);
    }
}