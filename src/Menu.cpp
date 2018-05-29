/*
** EPITECH PROJECT, 2018
** Indie Studio
** File description:
** Menu
*/

#include "Menu.hpp"
#include <iostream>


Menu::Menu()
	: _step(1), _nbPlayer(4), _change_menu(true), _changeState(true), _changed(false)
{
	makeMainMenu();
}

Menu::~Menu()
{
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
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 1, "Number Player :", 100, 150, 300, 100)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 2, "+", 200, 325, 100, 100)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 3, std::to_string(_nbPlayer), 200, 475, 100, 100)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 4, "-", 200, 625, 100, 100)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 5, "Game name :", SCREEN_WIDTH / 2 - 150, 150, 300, 70)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::INPUT, 6, "Game1" , SCREEN_WIDTH / 2 - 150, 220, 300, 100)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 7, "Start Game", SCREEN_WIDTH / 2 - 150, SCREEN_WIDTH / 2 - 150, 300, 100)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 8, "", SCREEN_WIDTH - 450, 0, 820, 1000)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::CHECKBOX, 9, "", SCREEN_WIDTH - 400, 200, 50, 50)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 10, "Bomb Up", SCREEN_WIDTH - 350, 200, 250, 50)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::CHECKBOX, 11, "", SCREEN_WIDTH - 400, 300, 50, 50)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 12, "Power Up", SCREEN_WIDTH - 350, 300, 250, 50)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::CHECKBOX, 9, "", SCREEN_WIDTH - 400, 400, 50, 50)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 14, "Penetration", SCREEN_WIDTH - 350, 400, 250, 50)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::CHECKBOX, 9, "", SCREEN_WIDTH - 400, 500, 50, 50)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 16, "Speed", SCREEN_WIDTH - 350, 500, 250, 50)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::CHECKBOX, 9, "", SCREEN_WIDTH - 400, 600, 50, 50)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 18, "Wall Pass", SCREEN_WIDTH - 350, 600, 250, 50)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::CHECKBOX, 9, "", SCREEN_WIDTH - 400, 700, 50, 50)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 20, "Kick", SCREEN_WIDTH - 350, 700, 250, 50)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 21, "Your pseudo", SCREEN_WIDTH / 2 - 150, 370, 300, 70)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::INPUT, 22, "Toto", SCREEN_WIDTH / 2 - 150, 440, 300, 100)));
}

void 	Menu::makeMapMenu()
{
	_item.clear();
	std::vector<std::wstring> toto;
	toto.push_back(L"map1");
	toto.push_back(L"map2");
	toto.push_back(L"map3");
	toto.push_back(L"map4");
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LABEL, 1, "Select your map", 500, 175, 600, 75)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::LISTBOX, 2, "", 500, 250, 600, 400)));
	static_cast<MenuItem*>(_item[1].get())->setChoices(toto);
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 3, "Start Game", 700, 700, 200, 100)));
}

void    Menu::makeMainMenu()
{
	_item.clear();
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 1, "Start Game", (SCREEN_WIDTH / 2) - 300, 280, 600, 100)));
	_item.push_back(std::unique_ptr<IEntity>(new MenuItem(Entity::BUTTON, 2, "Join Game", (SCREEN_WIDTH / 2) - 300, 430, 600, 100)));
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
			makeOptionMenu();
			break;
		case 3:
			makeJoinMenu();
			break;
		// case 4:
		// 	makeMapMenu(); Sayonara
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
//		_step = 4; // Sayonara
		_change_menu = true;
		state = STATE::GAME; // Sayonara
	}
	else if (actions.buttonPressed == 2) {
		if (_nbPlayer < 4)
			_nbPlayer += 1;
		static_cast<MenuItem*>(_item[2].get())->setText(std::to_string(_nbPlayer));
		_changeState = true;
	}
	else if (actions.buttonPressed == 4) {
		if (_nbPlayer > 2)
			_nbPlayer -= 1;
		static_cast<MenuItem*>(_item[2].get())->setText(std::to_string(_nbPlayer));
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

void 	Menu::handleMapMenu(Actions &actions, STATE &state)
{
	if (actions.escape == true) {
		_change_menu = true;
		_changed = true;
		_step = 2;
	} else if (actions.buttonPressed == 3) {
		state = STATE::GAME;
		_changed = true;
	}
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
			handleSecondMenu(actions, state);
			break;
		case 3:
			handleThirdMenu(actions, state);
			break;
		// case 4:
		// 	handleMapMenu(actions, state);
		// 	break; Sayonara
	}
}