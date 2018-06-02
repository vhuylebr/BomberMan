/*
** EPITECH PROJECT, 2018
** Indie Studio
** File description:
** Menu
*/

#include "Menu.hpp"
#include <iostream>


Menu::Menu()
	: _step(1), _nbPlayer(1), _nbBots(4), _mapH(50), _mapW(50), _change_menu(true), _changeState(true), _changed(false)
{
	makeMainMenu();
	initMaps();
}

void	Menu::initMaps()
{
	_maps.push_back({"img1.png", "Map 1", "map1.txt"});
	_maps.push_back({"img2.png", "Map 2", "map2.txt"});
	_maps.push_back({"empty", "Random", "empty"});
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
	toto.push_back(L"Save1");
	toto.push_back(L"Save2");
	toto.push_back(L"Save3");
	toto.push_back(L"Save4");

	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LISTBOX, 1, "", (SCREEN_WIDTH / 2) - 300, 250, 600, 400)));
	static_cast<MenuItem*>(_item[0].get())->setChoices(toto);
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 2, "Select Game to load : ", (SCREEN_WIDTH / 2) - 300, 150, 600, 100)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 3, "Connect", (SCREEN_WIDTH / 2) - 300, 700, 600, 100)));
}

void    Menu::makeOptionMenu()
{
	_item.clear();
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 1, "Number of Players :", 100, 300, 400, 90)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 2, "+", 400, 400, 100, 100)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 3, std::to_string(_nbPlayer), 250, 400, 100, 100)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 4, "-", 100, 400, 100, 100)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 5, "Game name :", 780, 120, 400, 70)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::INPUT, 6, "Game1" , 780, 190, 400, 70)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 7, "Start Game", 780, 800, 400, 100)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 8, "", SCREEN_WIDTH - 450, 0, 820, 1000)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::CHECKBOX, 9, "", SCREEN_WIDTH - 400, 200, 50, 50)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 10, "Bomb Up", SCREEN_WIDTH - 350, 200, 250, 50)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::CHECKBOX, 11, "", SCREEN_WIDTH - 400, 300, 50, 50)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 12, "Power Up", SCREEN_WIDTH - 350, 300, 250, 50)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::CHECKBOX, 13, "", SCREEN_WIDTH - 400, 400, 50, 50)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 14, "Penetration", SCREEN_WIDTH - 350, 400, 250, 50)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::CHECKBOX, 15, "", SCREEN_WIDTH - 400, 500, 50, 50)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 16, "Speed", SCREEN_WIDTH - 350, 500, 250, 50)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::CHECKBOX, 17, "", SCREEN_WIDTH - 400, 600, 50, 50)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 18, "Wall Pass", SCREEN_WIDTH - 350, 600, 250, 50)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::CHECKBOX, 19, "", SCREEN_WIDTH - 400, 700, 50, 50)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 20, "Kick", SCREEN_WIDTH - 350, 700, 250, 50)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 21, "Your name :", 100, 120, 400, 70)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::INPUT, 22, "Toto", 100, 190, 400, 70)));
	// Number of Bots
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 23, "+", 400, 640, 100, 100)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 24, std::to_string(_nbBots), 250, 640, 100, 100)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 25, "-", 100, 640, 100, 100)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 26, "Number of Bots :", 100, 540, 400, 90)));
	// Map height
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 27, "Map Height :", 780, 300, 400, 90)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 28, "+", 1080, 400, 100, 100)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 29, std::to_string(_mapH), 930, 400, 100, 100)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 30, "-", 780, 400, 100, 100)));
	// Map width
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 31, "Map Width :", 780, 540, 400, 90)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 32, "+", 1080, 640, 100, 100)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 33, std::to_string(_mapW), 930, 640, 100, 100)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 34, "-", 780, 640, 100, 100)));
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
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 1, "Start Game", (SCREEN_WIDTH / 2) - 300, 280, 600, 100)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 2, "Load Game", (SCREEN_WIDTH / 2) - 300, 430, 600, 100)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 3, "Quit", (SCREEN_WIDTH / 2) - 300, 580, 600, 100)));
}

void Menu::changeMenu()
{
	_change_menu = false;
	switch (_step) {
		case 1:
			makeMainMenu();
			break;
		case 2:
			makeModeMenu();
//			makeOptionMenu();
			break;
		case 3:
			makeJoinMenu();
			break;
		case 4:
		 	makeMapMenu();
			break;
	}
}

void Menu::handleFirstMenu(Actions &actions, STATE &state)
{
	if (actions.space || actions.enter || actions.buttonPressed != -1) {
		if (actions.buttonPressed != -1)
			_step = actions.buttonPressed;
		if (_step == 3)
			state = STATE::EXIT;
		if (_step == 2) {
			_step = 3;
			_changed = true;
		}
		if (_step == 1) {
			_step = 2;
			_changed = true;
		}
		_change_menu = true;
		actions.buttonPressed = 0;
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


void 	Menu::handleSecondMenu(Actions &actions, STATE &state)
{
	if (actions.escape == true) {
		_change_menu = true;
		_step = 1;
		_changeState = true;
		_changed = true;
	}
	if (actions.buttonPressed == 7) {
		_changed = true;
		_change_menu = true;
		state = STATE::GAME;
	}
	else if (actions.buttonPressed == 2) {
		if (_nbPlayer < 2)
			_nbPlayer += 1;
		static_cast<MenuItem*>(_item[2].get())->setText(std::to_string(_nbPlayer));
		_changeState = true;
	}
	else if (actions.buttonPressed == 4) {
		if (_nbPlayer > 1)
			_nbPlayer -= 1;
		static_cast<MenuItem*>(_item[2].get())->setText(std::to_string(_nbPlayer));
		_changeState = true;
	}
	else if (actions.buttonPressed == 23) {
		if (_nbBots < 10)
			_nbBots += 1;
		static_cast<MenuItem*>(_item[23].get())->setText(std::to_string(_nbBots));
		_changeState = true;
	}
	else if (actions.buttonPressed == 25) {
		if (_nbBots > 0)
			_nbBots -= 1;
		static_cast<MenuItem*>(_item[23].get())->setText(std::to_string(_nbBots));
		_changeState = true;
	}
	else if (actions.buttonPressed == 28) {
		if (_mapH < 100)
			_mapH += 10;
		static_cast<MenuItem*>(_item[28].get())->setText(std::to_string(_mapH));
		_changeState = true;
	}
	else if (actions.buttonPressed == 30) {
		if (_mapH > 10)
			_mapH -= 10;
		static_cast<MenuItem*>(_item[28].get())->setText(std::to_string(_mapH));
		_changeState = true;
	}
	else if (actions.buttonPressed == 32) {
		if (_mapW < 100)
			_mapW += 10;
		static_cast<MenuItem*>(_item[32].get())->setText(std::to_string(_mapW));
		_changeState = true;
	}
	else if (actions.buttonPressed == 34) {
		if (_mapW > 10)
			_mapW -= 10;
		static_cast<MenuItem*>(_item[32].get())->setText(std::to_string(_mapW));
		_changeState = true;
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
		item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, i + 2, "", ((i + 1) * (SCREEN_WIDTH / 5)) + 100, 400, 100, 100)));
		// set la texture + set le isSetTexture à true
		//_item.setTexture(true);
		//_item.setTexture(*(_map.begin()).imgFileName);
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
		_changed = true;
		actions.escape = false;
		_step = 2;
	} else if (actions.buttonPressed == 1) {
		std::cout << "Rotate left\n";
		rotateMaps(true);
		_changed = true;
	} else if (actions.buttonPressed == 5) {
		rotateMaps(false);
		_changed = true;
	}
	actions.buttonPressed = 0;
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
	return (actions.buttonPressed != -1 || actions.enter || actions.space
	|| actions.up || actions.down || actions.escape || changeState == true);
}

bool 	Menu::getState(Actions &actions, STATE &state)
{
 	// if (_step == 4 && actions.buttonPressed == 3) {
		// state = STATE::GAME;
 	// 	return false;
 	// } Sayonara
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
	return _item[id - 1];
}

std::vector<std::unique_ptr<IEntity>> &Menu::getMenuItems()
{
	return _item;
}

void Menu::getMenu(Actions &actions, STATE &state)
{
	if (_change_menu == true)
		changeMenu();
	switch (_step) {
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
	}
}