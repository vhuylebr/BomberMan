#include "Core.hpp"

Core::Core()
    :_state(STATE::MENU), _menu(), _lib(_act)
{
}

#include <unistd.h>

void    Core::menuManager(STATE &last)
{
    char a = 'a';
    _act = _lib.getActions();
    _menu.getMenu(a, _act, last); // Il faut faire une fonction action afin de check seulement si de nouvelles, bref il faut faire un truc ici
    if (_menu.changeState() == true) {
        _lib.affMenuItems(_menu.getMenu(a, _act, last));
    }
    _lib.drawMenu();
    // Les lignes qui suivent sont censées afficher les bonus qu'on a sélectionné mais ça segfault

    // std::vector<eItem> bonus = _menu.getBonus();
    // std::cout << "Bonus:" << std::endl;
    // if (!bonus.empty())
    //     for (auto &i : bonus) {
    //         std::cout << itemToStr(i) << std::endl;
    //     }
    // std::cout << std::endl;
    // sleep(2);
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
    while (_state != STATE::EXIT && _lib.getRun()) {
        if (_state == STATE::MENU)
            menuManager(_state);
        // else if (_state == STATE::LOBBY)
        //     lobbyManager(lstate);
        // else if (_state == STATE::GAME)
        //     gameManager(lstate);
    }
    return 0;
}