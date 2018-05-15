#include "Core.hpp"

Core::Core()
    :_state(STATE::MENU), _menu(), _lib(_act)
{
}

void    Core::menuManager(STATE &last)
{
    // state = state;
    char a = 'a';
    _act = _lib.getActions();
    _lib.affMenuItems(_menu.getMenu(a, _act, last));
}

// void    Core::lobbyManager(STATE &last)
// {
//     //last = state;
// }

// void    Core::gameManager(STATE &last)
// {
//     last = last;
    
//     if (_host) {
        
//     } else {
        
//     }
// }

int     Core::run()
{
    STATE lstate = _state;

    while (_state != STATE::EXIT && _lib.getRun()) {
        if (_state == STATE::MENU)
            menuManager(lstate);
        // else if (_state == STATE::LOBBY)
        //     lobbyManager(lstate);
        // else if (_state == STATE::GAME)
        //     gameManager(lstate);
    }
    return 0;
}