//#include <unistd.h>
#include "Core.hpp"
#include "Music.hpp"

Core::Core()
	:_state(STATE::MENU), _game(), _menu(), _lib(_act), _host(-1)
{
}

void 	Core::menuManager(STATE &last)
{
//	std::cout << "changed : " << _menu.stepChanged(last) << std::endl;
//	std::cout << "1" << std::endl;
	_act = _lib.getActions();
//	std::cout << "2" << std::endl;
	_lib.displayBackground();
//	std::cout << "3" << std::endl;
//	std::cout << "changed : " << _menu.stepChanged(last) << std::endl;
	if (_menu.getState(_act, _state) == true) {
		_menu.getMenu(_act, _state);
		if (_menu.isLabelToUpdate()) {
			auto ids = _menu.getIdToUpdate(_act);
			for (auto &id: ids)
				_lib.updateLabel(_menu.getItemByID(id));
		}
	}
//	std::cout << "changed : " << _menu.stepChanged(last) << std::endl;
//	std::cout << "4" << std::endl;
	if (_menu.stepChanged(last) == true) {
		std::cout << "i go here" << std::endl;
		_menu.getMenu(_act, _state);
		std::cout << "then here" << std::endl;
		_lib.cleanMenu();
		std::cout << "and finally here" << std::endl;
	}
//	std::cout << "5" << std::endl;
	if (last == STATE::GAME || last == STATE::INIT) {
		_lib.initMenu(_menu.getMenuItems());
		_menu.getMenu(_act, _state);
		_state = STATE::MENU;
		last = STATE::MENU;
	}
//	std::cout << "6" << std::endl;
	_lib.drawMenu();
}

static const t_bonus bonusButton[NB_ITEMS] {
	{9, eItem::BOMB_UP},
	{11, eItem::POWER_UP},
	{13, eItem::SUPER_BOMB},
	{15, eItem::SPEED},
//	{17, eItem::WALL_PASS},
	{19, eItem::KICK},
	{44, eItem::SHIELD},
};

int 	Core::getParametersFromMenu()
{
	if (_menu.getStep() == 5) {
		_param.map = _menu.getMap();
		_param.state = GameState::NEWGAME;
		_param.gameName = _lib.getInputText(_menu.getItemByID(6));
		_param.nbPlayers = _menu.getNbPlayer();
		_param.nbBots = _menu.getNbBots();
		_param.mapSize.first = _menu.getMapSize();
		_param.mapSize.second = _menu.getMapSize();
		_param.mapname = _param.map.mapName;
		_param.split = _param.nbPlayers - 1;
		for (int i = 0; i < NB_ITEMS; i++)
			if (_lib.getCheckboxState(_menu.getItemByID(bonusButton[i].id)) == true)
				_param.bonuses.push_back(bonusButton[i].bonus);
	} else if (_menu.getStep() == 3) {
		_param.state = GameState::LOADGAME;
		_param.gameName = _lib.getListBoxChoice(_menu.getItemByID(1));
		if (_param.gameName == L"")
			return (-1);
		_param.mapname = "./media/map1.txt";
	}
	return (0);
}

static void setPauseVisible(IrrLib &lib, bool state)
{
	lib.setVisible(state, PAUSE_ID);
	lib.setVisible(state, PAUSE_ID + 1);
	lib.setVisible(state, PAUSE_ID + 2);
	lib.setVisible(state, PAUSE_ID + 3);
}

static void setEndVisible(IrrLib &lib, bool state, char player)
{
	if (player == 1)
		lib.setVisible(state, WIN_P1_ID);
	else if (player == 2)
		lib.setVisible(state, WIN_P2_ID);
	else
		lib.setVisible(state, LOSE_ID);
	lib.setVisible(state, PLAY_AGAIN_ID);
	lib.setVisible(state, QUIT_END_ID);
}

void	Core::gameManager(STATE &last)
{
	if (last == STATE::MENU) {
		_game.init(_param);
		_lib.setSplitScreen(_game.getSplitState());
		_lib.initGame(_game.getSize(), _game.getMobileEntities());
	} else if (_state == STATE::PAUSE) {
		_game.handlePause(_lib.getActions(), _state);
		_lib.drawGame();
		if (_state == STATE::GAME)
			setPauseVisible(_lib, false);
	} else if (_state == STATE::END) {
		_game.handleEnd(_lib.getActions(), _state);
		_lib.drawGame();
		if (_state == STATE::GAME) {
			setEndVisible(_lib, false, _game.getEndId());
			_game.init(_param);
			_lib.setSplitScreen(_param.split);
			_lib.initGame(_game.getSize(), _game.getMobileEntities());
		}
	} else if (_host || true) { // Forcing true for now
		auto actions = _lib.getActions();
		if (actions.escape == true) {
			_lib.newMenuItems(_game.createPause());
			setPauseVisible(_lib, true);
			_state = STATE::PAUSE;
		}
		_lib.affGameEntities(_game.calc(actions, _state));
		_lib.removeEntities(_game.getEntitiesToRemove());
		_lib.drawGame();
		if (_state == STATE::END) {
			_lib.newMenuItems(_game.createEndScreen());
			setEndVisible(_lib, true, _game.getEndId());
		}
	}
	last = STATE::GAME;
}

int		Core::startMusic()
{
	if (_coremusic.load(SOUND::MENU, "./media/Sound/MenuSelect.ogg") == false)
		return -1;
	if (_coremusic.load(SOUND::GAME, "./media/Sound/TitleScreen.ogg") == false)
		return -1;
	_coremusic.setLoop(SOUND::MENU, true);
	_coremusic.play(SOUND::MENU);
	return 0;
}

int	Core::loop()
{
	STATE   lstate = STATE::INIT;

	if (startMusic() == -1)
		return -1;
	while (_state != STATE::EXIT && _lib.getRun()) {
//		std::cout << "toto" << std::endl;
		if (_state == STATE::MENU) {
//			std::cout << "menu on" << std::endl; 
			menuManager(lstate);
//			std::cout << "menu off" << std::endl; 
			if (_state == STATE::GAME) {
				std::cout << "switch on" << std::endl;
				_coremusic.stop(SOUND::MENU);
				_coremusic.setLoop(SOUND::GAME, true);
				_coremusic.play(SOUND::GAME);
				std::cout << "switch ongoing" << std::endl;
				if (getParametersFromMenu() == -1) {
					_state = STATE::MENU;
					continue;
				std::cout << "switch off" << std::endl;
				}
				std::cout << "clean on" << std::endl;
				_lib.cleanMenu();
				std::cout << "clean off" << std::endl;
				while(1);
			}
		} else if (_state == STATE::GAME || _state == STATE::PAUSE
		|| _state == STATE::END)
			gameManager(lstate);
	}
	_lib.dropAll();
	return 0;
}
