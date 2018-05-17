#include <unistd.h>
#include "Core.hpp"

Core::Core()
    :_state(STATE::MENU), _game(), _menu(), _lib(_act), _host(-1)
{
}

void    Core::menuManager(STATE &last)
{
    char a = 'a';
    _act = _lib.getActions();
    if (_menu.getState(a, _act, last) == true)
        _lib.affMenuItems(_menu.getMenu(a, _act, _state));
    // if (_menu.changeState() == true) {
    _lib.drawMenu();

    last = STATE::MENU;
    // Les lignes qui suivent sont censées afficher les bonus qu'on a sélectionné mais ça segfault

    // std::vector<eItem> bonus = _menu.getBonus();
    // std::cout << "Bonus:" << std::endl;
    // if (!bonus.empty())
    // for (auto &i : bonus) {
    //      std::cout << itemToStr(i) << std::endl;
    // }
    // std::cout << std::endl;
    // sleep(2);
}

// void    Core::lobbyManager(STATE &last)
// {
//     //last = state;
// }

parameters 	Core::getParameters()
{
	parameters pm;

	if (_menu.getStep() == 2) { // Menu création
		std::wcout << L"lol : " << _lib.getLabelText(_menu.getItemByID(10)) << std::endl;
		bool l = _lib.getCheckboxState(_menu.getItemByID(9));
		std::cout << "l : " << l << std::endl;
		pm.mapSize = std::make_pair(10, 10);
		pm.nbPlayers = std::stoi(_lib.getLabelText(_menu.getItemByID(3)));
	}
	else if (_menu.getStep() == 3) // Menu load
	{
		// read file toussa toussa
	}
	return (pm);
}

void    Core::gameManager(STATE &last)
{
    if (last == STATE::MENU)
        _game.init(std::make_pair(10, 10)); // Deserialization from file or new here
    else if (_host || true) { // Forcing true for now
       /*_lib.affEntities(*/_game.calc(_lib.getActions()); /*) */
    }
    last = STATE::GAME;
}

int     Core::loop()
{
    STATE   lstate = STATE::MENU;
    //_state = STATE::GAME; // Game
    while (_state != STATE::EXIT && _lib.getRun()) {
        if (_state == STATE::MENU)
            menuManager(lstate);
        // else if (_state == STATE::LOBBY)
        //     lobbyManager(lstate);
        else if (_state == STATE::GAME)
             gameManager(lstate);
    }
    return 0;
}