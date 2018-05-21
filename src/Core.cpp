#include <SFML/Audio.hpp>
#include <unistd.h>
#include "Core.hpp"

Core::Core()
	:_state(STATE::MENU), _game(), _menu(), _lib(_act), _host(-1)
{
}

void 	Core::menuManager(STATE &last)
{
	_act = _lib.getActions();
	_lib.displayBackground();

	if (_menu.getState( _act, _state) == true) {
		_menu.getMenu(_act, _state);
		if (_menu.getStep() == 2 && (_act.buttonPressed == 2 || _act.buttonPressed == 4))
			_lib.updateLabel(_menu.getItemByID(3));
	}
	if (_menu.stepChanged(last) == true) {
		_menu.getMenu(_act, _state);
	}
	if (last == STATE::GAME || last == STATE::INIT) {
		_lib.initMenu(_menu.getMenuItems());
		_menu.getMenu(_act, _state);
		_state = STATE::MENU;
		last = STATE::MENU;
	}
	_lib.drawMenu();
}

static const t_bonus bonusButton[NB_ITEMS] {
	{9, eItem::BOMB_UP},
	{11, eItem::POWER_UP},
	{13, eItem::SUPER_BOMB},
	{15, eItem::SPEED},
	{17, eItem::WALL_PASS},
	{19, eItem::KICK},
};

void 	Core::getParametersFromMenu()
{
	if (_menu.getStep() == 2) {
		_param.state = GameState::NEWGAME;
		_param.gameName = _lib.getInputText(_menu.getItemByID(6));
		_param.nbPlayers = std::stoi(_lib.getLabelText(_menu.getItemByID(3)));
		_param.mapSize = std::make_pair(10, 10);
		for (int i = 0; i < NB_ITEMS; i++)
			if (_lib.getCheckboxState(_menu.getItemByID(bonusButton[i].id)) == true)
				_param.bonuses.push_back(bonusButton[i].bonus);
		std::wcout << L"game name : " << _param.gameName << std::endl;
		std::cout << "nb players : " << _param.nbPlayers << std::endl;
		std::cout << "size : " << _param.bonuses.size() << std::endl;;
	}
	else if (_menu.getStep() == 3)
	{
		_param.state = GameState::LOADGAME;
		_param.gameName = _lib.getListBoxChoice(_menu.getItemByID(1));
		std::wcout << L"game name : " << _param.gameName << std::endl;
	}
}

void    Core::gameManager(STATE &last)
{
	if (last == STATE::MENU) {
		_game.init(std::make_pair(5, 5));
		_lib.initGame(_game.getEntities(), _game.getSize());
	} else if (_host || true) { // Forcing true for now
		_lib.affGameEntities(_game.calc(_lib.getActions()));
		_lib.drawGame();
	}
	last = STATE::GAME;
}

int     Core::loop()
{
	STATE   lstate = STATE::INIT;
	sf::Music music;

	while (_state != STATE::EXIT && _lib.getRun()) {
		if (_state == STATE::MENU) {
			menuManager(lstate);
			if (_state == STATE::GAME) {
				if (!music.openFromFile("./media/Sound/MenuSelect.ogg"))
					return -1;
				music.play();
				music.setLoop(true);
				getParametersFromMenu();
				_lib.cleanMenu();
			}
		} else if (_state == STATE::GAME) {
			gameManager(lstate);
		}
	}
	return 0;
}
