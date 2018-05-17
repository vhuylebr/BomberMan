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
	_lib.displayBackground();
	if (_menu.getState(a, _act, _state) == true || _menu.stepChanged() == true) {
		_lib.affMenuItems(_menu.getMenu(a, _act, _state));
	}
	_lib.drawMenu();

	last = STATE::MENU;
}

// void    Core::lobbyManager(STATE &last)
// {
//     //last = state;
// }

void 	Core::getParameters()
{
	if (_menu.getStep() == 2) {
		_param.gameName = _lib.getInputText(_menu.getItemByID(6));
		_param.nbPlayers = std::stoi(_lib.getLabelText(_menu.getItemByID(3)));
		_param.mapSize = std::make_pair(10, 10);

		if (_lib.getCheckboxState(_menu.getItemByID(9)) == true)
			_param.bonuses.push_back(eItem::BOMB_UP);
		if (_lib.getCheckboxState(_menu.getItemByID(11)) == true)
			_param.bonuses.push_back(eItem::POWER_UP);
		if (_lib.getCheckboxState(_menu.getItemByID(13)) == true)
			_param.bonuses.push_back(eItem::SUPER_BOMB);
		if (_lib.getCheckboxState(_menu.getItemByID(15)) == true)
			_param.bonuses.push_back(eItem::SPEED);
		if (_lib.getCheckboxState(_menu.getItemByID(17)) == true)
			_param.bonuses.push_back(eItem::WALL_PASS);
		if (_lib.getCheckboxState(_menu.getItemByID(19)) == true)
			_param.bonuses.push_back(eItem::KICK);
	}
	else if (_menu.getStep() == 3)
	{
		std::wcout << L"file name : " << _lib.getInputText(_menu.getItemByID(1)) << std::endl; // Get nom du fichier à charger
		// read file toussa toussa
	}
}

void    Core::gameManager(STATE &last)
{
	if (last == STATE::MENU) {
		_game.init(std::make_pair(10, 10));
		_lib.initGame(_game.getEntities(), _game.getSize());
	} else if (_host || true) { // Forcing true for now
	   _lib.affGameEntities(_game.calc(_lib.getActions()));
	   _lib.drawGame();
	}
	last = STATE::GAME;
}

int     Core::loop()
{
	STATE   lstate = STATE::MENU;
	while (_state != STATE::EXIT && _lib.getRun()) {
		if (_state == STATE::MENU) {
			menuManager(lstate);
			if (_state == STATE::GAME) {
				getParameters();
				_lib.cleanMenu();
			}
		} else if (_state == STATE::GAME)
			gameManager(lstate);
	}
	return 0;
}
