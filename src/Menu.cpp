/*
** EPITECH PROJECT, 2018
** Indie Studio
** File description:
** Menu
*/

#include "Menu.hpp"
#include <iostream>
#include <experimental/filesystem>

Menu::Menu()
	: _start(0), _step(0), _nbPlayer(1), _nbBots(4), _mapH(50), _mapW(50), _change_menu(true), _changeState(true), _changed(false)
{
	makeMainMenu();
	initMaps();
}

void	Menu::initMaps()
{
	// _maps.push_back({"media/img1.png", "Map 1", "map1.txt"});
	// _maps.push_back({"media/img2.png", "Map 2", "map2.txt"});
	_maps.push_back({"media/maps.1/lvl1.jpg", "Lvl 1", "media/maps.1/lvl1.txt"});
	_maps.push_back({"media/maps.1/lvl2.jpg", "Lvl 2", "media/maps.1/lvl2.txt"});
	_maps.push_back({"media/maps.1/lvl3.jpg", "Lvl 3", "media/maps.1/lvl3.txt"});
	_maps.push_back({"media/maps.1/lvl4.jpg", "Lvl 4", "media/maps.1/lvl4.txt"});
	_maps.push_back({"media/map-t.jpg", "Map T", "media/mapT.txt"});
	_maps.push_back({"media/random.png", "Random", "empty"});
	_maps.push_back({"media/map-x.jpg", "Map X", "media/mapX.txt"});
	_maps.push_back({"media/map-m.png", "Map M", "media/mapM.txt"});
	_maps.push_back({"media/maps.1/megamap.jpg", "MegaMap", "media/mapGiga.txt"});
	_sizeMap = 10;
}

Menu::~Menu()
{
	_item.clear();
	_maps.clear();
	_bonus.clear();
}

void 	Menu::makeJoinMenu()
{
	_item.clear();
	std::vector<std::wstring> toto;
//    std::string path = MAPS_DIRECTORY;
	std::string path = "./media/maps/";
	try {
	    for (auto &p : std::experimental::filesystem::directory_iterator(path)) {
			std::string file = p.path().string();
			std::wstring ws;
			ws.assign(file.begin(), file.end());
			toto.push_back(ws);
		}
	} catch (const std::experimental::filesystem::filesystem_error &e) {
		std::cout << "Error occured : Maps folder does not exist" << std::endl;
		std::cout << e.what() << std::endl;
		exit(84);
	}
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LISTBOX, 1, "", (SCREEN_WIDTH / 2) - 300, 250, 600, 400)));
	static_cast<MenuItem*>(_item[0].get())->setChoices(toto);
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 2, "Select Game to load : ", (SCREEN_WIDTH / 2) - 300, 150, 600, 100)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 3, "Connect", (SCREEN_WIDTH / 2) - 300, 700, 600, 100)));
}

void    Menu::makeModeMenu()
{
	_item.clear();
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 1, "1 Player", (SCREEN_WIDTH * 0.1), 400, 600, 180)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 2, "2 Player", (SCREEN_WIDTH * 0.55), 400, 600, 180)));
}

void    Menu::makeMainMenu()
{
	_item.clear();
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 6, "", (SCREEN_WIDTH / 2) - 650, 100, 1260, 350, "media/title.png", true)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 1, "Start Game", (SCREEN_WIDTH / 2) - 300, 520, 600, 100)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 2, "Load Game", (SCREEN_WIDTH / 2) - 300, 650, 600, 100)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 3, "Quit", (SCREEN_WIDTH / 2) - 300, 780, 600, 100)));
}

void	Menu::makeParamsMenu()
{
	if (_map.mapName == "Random") {
		_randomMode = true;
		_nbBotsMax = _sizeMap - (2 * (_sizeMap / 10)) - 2;
	} else {
		_randomMode = false;
		_nbBotsMax = 2;
	}
	_nbBots = _nbBotsMax;
	_item.clear();
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 5, "Game name :", 780, 120, 400, 70)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::INPUT, 6, "BestGameEver" , 780, 190, 400, 70)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 7, "Start Game", 765, 700, 435, 150)));

	// Bonus
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 8, "", SCREEN_WIDTH - 450, 0, 820, 1000)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::CHECKBOX, 9, "", SCREEN_WIDTH - 400, 200, 50, 50)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 10, "Bomb Up", SCREEN_WIDTH - 350, 200, 250, 50)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::CHECKBOX, 11, "", SCREEN_WIDTH - 400, 300, 50, 50)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 12, "Power Up", SCREEN_WIDTH - 350, 300, 250, 50)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::CHECKBOX, 13, "", SCREEN_WIDTH - 400, 400, 50, 50)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 14, "Penetration", SCREEN_WIDTH - 350, 400, 250, 50)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::CHECKBOX, 15, "", SCREEN_WIDTH - 400, 500, 50, 50)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 16, "Speed", SCREEN_WIDTH - 350, 500, 250, 50)));
//	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::CHECKBOX, 17, "", SCREEN_WIDTH - 400, 600, 50, 50)));
//	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 18, "Wall Pass", SCREEN_WIDTH - 350, 600, 250, 50)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::CHECKBOX, 19, "", SCREEN_WIDTH - 400, 600, 50, 50)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 20, "Kick", SCREEN_WIDTH - 350, 600, 250, 50)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::CHECKBOX, 44, "", SCREEN_WIDTH - 400, 700, 50, 50)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 45, "Shield", SCREEN_WIDTH - 350, 700, 250, 50)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::CHECKBOX, 46, "", SCREEN_WIDTH - 400, 800, 50, 50)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 47, "BUBG", SCREEN_WIDTH - 350, 800, 250, 50)));


	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 21, "Name 1st player :", 100, 120, 400, 70)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::INPUT, 22, "Superman", 100, 190, 400, 70)));
	if (_nbPlayer == 2) {
		_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 21, "Name 2nd player :", 100, 330, 400, 70)));
		_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::INPUT, 22, "Batman", 100, 400, 400, 70)));
	}
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 23, "+", 400, 640, 100, 100)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 24, std::to_string(_nbBots), 250, 640, 100, 100)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 25, "-", 100, 640, 100, 100)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 26, "Number of Bots :", 100, 540, 400, 90)));
	// Map height
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 27, "Map size", 780, 300, 400, 90)));
	if (_randomMode == true) {
		_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 28, "+", 1080, 400, 100, 100)));
		_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 30, "-", 780, 400, 100, 100)));
	}
	// afficher les tailles qui sont dans Map
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 29,
	std::to_string(_sizeMap) + "x" + std::to_string(_sizeMap), 930, 400, 120, 100)));
}

void Menu::changeMenu()
{
	_change_menu = false;
	switch (_step) {
		case 0:
			makeIntroMenu();
			break;
		case 1:
			makeMainMenu();
			break;
		case 2:
			makeModeMenu();
			break;
		case 3:
			makeJoinMenu();
			break;
		case 4:
		 	makeMapMenu();
			break;
		case 5:
			makeParamsMenu();
			break;
	}
}

void Menu::handleFirstMenu(Actions &actions, STATE &state)
{
	if (actions.buttonPressed != -1) {
		if (actions.buttonPressed > 0)
			_step = actions.buttonPressed;
		if (_step == 3)
			state = STATE::EXIT;
		if (_step == 2) {
			_step = 3;
			_changed = true;
			actions.buttonPressed = 0;
		}
		if (_step == 1) {
			_step = 2;
			actions.buttonPressed = 0;
			_changed = true;
			actions.buttonPressed = 0;
		}
		_change_menu = true;
	}
}

void 	Menu::handleModeMenu(Actions &actions, STATE &state)
{
	if (actions.escape == true) {
		_change_menu = true;
		_step = 1;
		_changeState = true;
		_changed = true;
	}
	if (actions.buttonPressed == 1)
		_nbPlayer = 1;
	else if (actions.buttonPressed == 2)
		_nbPlayer = 2;
	if (actions.buttonPressed == 1 || actions.buttonPressed == 2) {
		_changed = true;
		_change_menu = true;
		_step = 4;
		actions.buttonPressed = 0;
	}
}

void 	Menu::handleThirdMenu(Actions &actions, STATE &state)
{
	if (actions.escape == true) {
		_change_menu = true;
		_changed = true;
		_step = 1;
	} else if (actions.buttonPressed == 3) {
		state = STATE::GAME;
		_changed = true;
	}
}

static void displayThreeMaps(std::vector<Map> &maps, std::vector<std::unique_ptr<IEntity>> &item)
{
	int size;

	for (int i = 0; i < 3; i++) {
		size = maps.begin()->mapName.size() * 20 + 20;
		if (size <= 100)
			item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 8, maps.begin()->mapName, ((i + 1) * (SCREEN_WIDTH / 5)) + 100, 300, maps.begin()->mapName.size() * 20 + 20, 40)));
		else
			item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 8, maps.begin()->mapName,
			((i + 1) * (SCREEN_WIDTH / 5)) + 100 - ((size - 100) / 2), 300, maps.begin()->mapName.size() * 20 + 20, 40)));
		item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, i + 2, "", ((i + 1) * (SCREEN_WIDTH / 5)), 400, 370, 370)));
		static_cast<MenuItem *>(item.back().get())->setTexture(maps.begin()->imgFileName);
		static_cast<MenuItem *>(item.back().get())->setTexture(true);
		std::rotate(maps.begin(), maps.begin() + 1, maps.end());
	}
}

void 	Menu::makeMapMenu()
{
	_item.clear();
	if (_maps.size() == 0)
		_maps.push_back({"empty", "Random", "empty"});
	// set une texture à < pour mettre une fleche
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 1, "<", (SCREEN_WIDTH / 5) / 2 - 50, 400, 100, 100)));
	displayThreeMaps(_maps, _item);
	for (int i = 0; i < 3; i++)
		std::rotate(_maps.rbegin(), _maps.rbegin() + 1, _maps.rend());
	// set une texture à < pour mettre une fleche
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 5, ">", (SCREEN_WIDTH / 5) * 4 + (SCREEN_WIDTH / 5) / 2 - 50, 400, 100, 100)));
}

void	Menu::rotateMaps(bool left)
{
	_item.clear();
	if (left)
		std::rotate(_maps.begin(), _maps.begin() + 1, _maps.end());
	else
		std::rotate(_maps.rbegin(), _maps.rbegin() + 1, _maps.rend());	
	if (_maps.size() == 0)
		_maps.push_back({"empty", "Random", "empty"});
	// set une texture à < pour mettre une fleche
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 1, "<", (SCREEN_WIDTH / 5) / 2 - 50, 400, 100, 100)));
	displayThreeMaps(_maps, _item);
	for (int i = 0; i < 3; i++)
		std::rotate(_maps.rbegin(), _maps.rbegin() + 1, _maps.rend());
	// set une texture à < pour mettre une fleche
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 5, ">", (SCREEN_WIDTH / 5) * 4 + (SCREEN_WIDTH / 5) / 2 - 50, 400, 100, 100)));
}

void 	Menu::handleMapMenu(Actions &actions, STATE &state)
{
	if (actions.escape == true) {
		_change_menu = true;
		actions.escape = false;
		_step = 2;
	} else if (actions.buttonPressed == 1) {
		rotateMaps(true);
		_changed = true;
	} else if (actions.buttonPressed == 5) {
		rotateMaps(false);
		_changed = true;
	} else if (actions.buttonPressed > 1) {
		for (int i = 2; i < actions.buttonPressed; i++)
			std::rotate(_maps.begin(), _maps.begin() + 1, _maps.end());
		_map = _maps.front();
		_change_menu = true;
		_step = 5;
		_changed = true;
		actions.escape = false;
	}
}

void 	Menu::handleParamsMenu(Actions &actions, STATE &state)
{
	if (actions.escape == true) {
		_change_menu = true;
		_step = 4;
		actions.escape = false;
	}
	if (actions.buttonPressed == 7) {
		state = STATE::GAME;
	} else if (actions.buttonPressed == 23) {
		if (_nbBots < _nbBotsMax)
			_nbBots += 1;
		static_cast<MenuItem*>(getItemByID(24).get())->setText(std::to_string(_nbBots));
		_changeState = true;
	} else if (actions.buttonPressed == 25 && !(_nbPlayer == 1 && _nbBots == 1)) {
		if (_nbBots > 0)
			_nbBots -= 1;
		static_cast<MenuItem*>(getItemByID(24).get())->setText(std::to_string(_nbBots));
		_changeState = true;
	} else if (actions.buttonPressed == 28) {
		if (_sizeMap < 100)
			_sizeMap += 10;
		_nbBotsMax = (_sizeMap - (2 * (_sizeMap / 10)) - 2);
		static_cast<MenuItem*>(getItemByID(29).get())->setText(std::to_string(_sizeMap) + "x" + std::to_string(_sizeMap));
		_changeState = true;
	} else if (actions.buttonPressed == 30) {
		if (_sizeMap > 10)
			_sizeMap -= 10;
		if (_nbBotsMax > (_sizeMap - (2 * (_sizeMap / 10)) - 2)) {
			_nbBotsMax = (_sizeMap - (2 * (_sizeMap / 10)) - 2);
			if (_nbBots > _nbBotsMax) {
				_nbBots = _nbBotsMax;
				static_cast<MenuItem*>(getItemByID(24).get())->setText(std::to_string(_nbBotsMax)); // ne s'update pas sur l'écran..
			}
		}
		static_cast<MenuItem*>(getItemByID(29).get())->setText(std::to_string(_sizeMap) + "x" + std::to_string(_sizeMap));
		_changeState = true;
	}
}

std::vector<int>	Menu::getIdToUpdate(const Actions &actions)
{
	if (getStep() == 2) {
		if (actions.buttonPressed == 2 || actions.buttonPressed == 4)
			return std::vector<int>({3});
		if (actions.buttonPressed == 23 || actions.buttonPressed == 25)
			return std::vector<int>({24});
		if (actions.buttonPressed == 28 || actions.buttonPressed == 30)
			return std::vector<int>({29});
		if (actions.buttonPressed == 32 || actions.buttonPressed == 34)
			return std::vector<int>({33});
	} else if (getStep() == 5) {
		if (actions.buttonPressed == 25 || actions.buttonPressed == 23)
			return std::vector<int>({24});
		if (actions.buttonPressed == 28 || actions.buttonPressed == 30)
			return std::vector<int>({29, 24});
	}
	return std::vector<int>({0});
}

bool 	Menu::stepChanged(STATE &state)
{
	if (_changed == true) {
		_changed = false;
		state = STATE::INIT;
		return true;
	}
	return false;
}

static bool keyPressed(Actions &actions, bool changeState)
{
	return (actions.buttonPressed != -1	|| actions.escape || changeState == true);
}

bool 	Menu::getState(Actions &actions, STATE &state)
{
	if (_step == 0 && ((std::clock() - _start ) / (double) CLOCKS_PER_SEC) > 0.5)
		return true;
 	if (_step == 2 && actions.buttonPressed == 7) {
		state = STATE::GAME;
 		return false;
 	}
	if (_step == 3 && actions.buttonPressed == 3) {
		state = STATE::GAME;
		return false;
	}
	if (keyPressed(actions, _changeState)) {
		_changeState = false;
		return true;
	}
	return false;
}

std::unique_ptr<IEntity> &Menu::getItemByID(int id)
{
	for (auto &i : _item) {
		if ((i.get())->getId() == id)
			return i;
	}
	return _item.front();
}

std::vector<std::unique_ptr<IEntity>> &Menu::getMenuItems()
{
	return _item;
}

void Menu::handleIntroMenu(Actions &actions)
{
	if (_start == 0)
		_start = std::clock();
	double duration;

	duration = ( std::clock() - _start ) / (double) CLOCKS_PER_SEC;
	if (duration > 0 && duration < 0.5)
//		actions.buttonPressed = 2;
		actions.escape = true;
	if (duration >= 0.5 && duration < 1) {
		_changeState = true;
		_changed = true;
		_item.clear();
		_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 6, "", (SCREEN_WIDTH / 2) - 650, 100, 1260, 350, "media/title.png", true)));
	} else if (duration >= 1 && duration < 1.5) {
		_changeState = true;
		_changed = true;
		_item.clear();
		_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 6, "", (SCREEN_WIDTH / 2) - 650, 100, 1260, 350, "media/title.png", true)));
		_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 1, "Start Game", (SCREEN_WIDTH / 2) - 300, 520, 600, 100)));
	} else if (duration >= 1.5 && duration < 2) {
		_changeState = true;
		_changed = true;
		_item.clear();
		_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 6, "", (SCREEN_WIDTH / 2) - 650, 100, 1260, 350, "media/title.png", true)));
		_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 1, "Start Game", (SCREEN_WIDTH / 2) - 300, 520, 600, 100)));
		_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 2, "Load Game", (SCREEN_WIDTH / 2) - 300, 650, 600, 100)));
	} else if (duration > 2) {
		_changeState = true;
		_changed = true;
		_item.clear();
		_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 6, "", (SCREEN_WIDTH / 2) - 650, 100, 1260, 350, "media/title.png", true)));
		_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 1, "Start Game", (SCREEN_WIDTH / 2) - 300, 520, 600, 100)));
		_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 2, "Load Game", (SCREEN_WIDTH / 2) - 300, 650, 600, 100)));
		_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 3, "Quit", (SCREEN_WIDTH / 2) - 300, 780, 600, 100)));
	}
	if (duration > 2.5 || (duration > 0.5 && actions.escape)) {
		_step = 1;
		_change_menu = true;
	}
}

void Menu::makeIntroMenu()
{
	_item.clear();
}

void Menu::getMenu(Actions &actions, STATE &state)
{
	if (_change_menu == true)
		changeMenu();
	switch (_step) {
		case 0:
			handleIntroMenu(actions);
			break;
		case 1:
			handleFirstMenu(actions, state);
			break;
		case 2:
			handleModeMenu(actions, state);
			break;
		case 4:
			handleMapMenu(actions, state);
			break;
		case 3:
			handleThirdMenu(actions, state);
			break;
		case 5:
			handleParamsMenu(actions, state);
			break;
	}
}