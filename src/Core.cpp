#include <unistd.h>
#include "Core.hpp"
#include "Music.hpp"

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
		_lib.cleanMenu();
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
		_param.mapname = "./media/map1.txt";
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
		_param.mapname = "./media/map1.txt";
		std::wcout << L"game name : " << _param.gameName << std::endl;
	}
}

void	Core::gameManager(STATE &last)
{
	if (last == STATE::MENU) {
		_game.init(_param);
		_lib.initGame(_game.getEntities(), _game.getSize(), _game.getMobileEntities());
	} else if (_state == STATE::PAUSE) {
		_game.handlePause(_lib.getActions(), _state);
		_lib.drawGame();
		if (_state == STATE::GAME)
			_lib.setVisible(false);
	} else if (_host || true) { // Forcing true for now
		auto actions = _lib.getActions();
		if (actions.escape == true) {
			_lib.createPause(_game.createPause());
			_lib.setVisible(true);
			_state = STATE::PAUSE;
		}
		_lib.affGameEntities(_game.calc(actions));
		_lib.removeEntities(_game.getEntitiesToRemove());
		_lib.drawGame();
	}
	last = STATE::GAME;
}

int		Core::startMusic()
{
	if (_coremusic.load(SOUND::MENU, "./media/Sound/MenuSelect.ogg") == false)
		return -1;
	if (_coremusic.load(SOUND::GAME, "./media/Sound/TitleScreen.ogg") == false)
		return -1;
	_coremusic.play(SOUND::MENU);
	_coremusic.setLoop(SOUND::MENU, true);
	return 0;
}

int	Core::loop()
{
	STATE   lstate = STATE::INIT;

	if (startMusic() == -1)
		return -1;
	while (_state != STATE::EXIT && _lib.getRun()) {
		if (_state == STATE::MENU) {
			menuManager(lstate);
			if (_state == STATE::GAME) {
				_coremusic.stop(SOUND::MENU);
				_coremusic.play(SOUND::GAME);
				_coremusic.setLoop(SOUND::GAME, true);
				getParametersFromMenu();
				_lib.cleanMenu();
			}
		} else if (_state == STATE::GAME || _state == STATE::PAUSE)
			gameManager(lstate);
	}
	_lib.dropAll();
	return 0;
}
