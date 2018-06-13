//#include <unistd.h>
#include "Core.hpp"
#include "Music.hpp"
#include <chrono>
#include <thread>

Core::Core()
	:_state(STATE::MENU), _game(), _menu(), _lib(_act), _host(-1)
{
}

void 	Core::menuManager(STATE &last)
{
	_act = _lib.getActions();
	_lib.displayBackground();
	if (_menu.getState(_act, _state) == true) {
		_menu.getMenu(_act, _state);
		if (_menu.isLabelToUpdate()) {
			auto ids = _menu.getIdToUpdate(_act);
			for (auto &id: ids)
				_lib.updateLabel(_menu.getItemByID(id));
		}
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

static const t_bonus bonusButton[NB_ITEMS + 1] {
	{9, eItem::BOMB_UP},
	{11, eItem::POWER_UP},
	{13, eItem::SUPER_BOMB},
	{15, eItem::SPEED},
	{19, eItem::KICK},
	{44, eItem::SHIELD},
	{46, eItem::BUBG},
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
		_param.bubg = _lib.getCheckboxState(_menu.getItemByID(bonusButton[6].id));
		std::cout << "BUBG : " << _param.bubg << std::endl;
		
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

static void introScreen(IrrLib &lib)
{
	std::clock_t start;
	double duration;

	start = std::clock();
	/* Your algorithm here */
	lib.setVisible(false, INTRO1_ID);
	lib.setVisible(false, INTRO2_ID);
	lib.setVisible(false, INTRO3_ID);
	lib.drawGame();
	while ((duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC) < 3) {
		if (duration < 1)
			lib.setVisible(true, INTRO3_ID);
		else if (duration > 1 && duration < 2) {
			lib.setVisible(false, INTRO3_ID);
			lib.setVisible(true, INTRO2_ID);
		} else if (duration > 2) {
			lib.setVisible(false, INTRO2_ID);
			lib.setVisible(true, INTRO1_ID);
		}
		lib.drawGame();
	}
	lib.setVisible(false, INTRO1_ID);
	lib.setVisible(false, INTRO2_ID);
	lib.setVisible(false, INTRO3_ID);
}

void	Core::gameManager(STATE &last, bool &initialization)
{
	if (last == STATE::MENU) {
		_game.init(_param);
		_lib.setSplitScreen(_game.getSplitState());
		_lib.initGame(_game.getSize(), _game.getMobileEntities());
		auto actions = _lib.getActions();
		_lib.affGameEntities(_game.calc(actions, _state, _param));
		if (actions.escape == true) {
			_lib.newMenuItems(_game.createPause());
			setPauseVisible(_lib, true);
			_state = STATE::PAUSE;
			return ;
		}
		_lib.drawGame();
		_lib.setSplitScreen(_param.split);
		if (initialization == false) {
			initialization = true;
			_lib.newMenuItems(_game.createLoadScreen());
		}
		introScreen(_lib);
	} else if (_state == STATE::PAUSE) {
		_game.handlePause(_lib.getActions(), _state);
		 if (_state == STATE::MENU)
		 	_lib.affGameEntities(_game.getAllMap());
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
		_lib.affGameEntities(_game.calc(actions, _state, _param));
		if (actions.escape == true) {
			_lib.newMenuItems(_game.createPause());
			setPauseVisible(_lib, true);
			_state = STATE::PAUSE;
			return ;
		}
		_lib.drawGame();
		_lib.setSplitScreen(_param.split);
		if (_state == STATE::END) {
			_lib.newMenuItems(_game.createEndScreen());
			setEndVisible(_lib, true, _game.getEndId());
			return;
		}
		_lib.removeEntities(_game.getEntitiesToRemove());
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
	_coremusic.setVol(SOUND::MENU, 0.8);
	_coremusic.setVol(SOUND::GAME, 0.3);
	return 0;
}

using namespace std::chrono;

int	Core::loop()
{
	STATE   lstate = STATE::INIT;
	bool initialization = false;

	if (startMusic() == -1)
		return -1;
	while (_state != STATE::EXIT && _lib.getRun()) {
		//_now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		if (_state == STATE::MENU) {
			initialization = false;
			menuManager(lstate);
			if (_state == STATE::GAME) {
				_coremusic.stop(SOUND::MENU);
				_coremusic.setLoop(SOUND::GAME, true);
				_coremusic.play(SOUND::GAME);
				if (getParametersFromMenu() == -1) {
					_state = STATE::MENU;
					continue;
				}
				_lib.cleanMenu();
			}
		} else if (_state == STATE::GAME || _state == STATE::PAUSE
		|| _state == STATE::END)
//	__int64_t later = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
//	std::this_thread::sleep_for(std::chrono::milliseconds(later - _now));
    gameManager(lstate, initialization);
	}
	return 0;
}
