/*
** EPITECH PROJECT, 2018
** Indie Studio
** File description:
** Menu
*/

#include "Menu.hpp"
#include <iostream>


Menu::Menu()
	: _step(1), _nbPlayer(4), _change_menu(true), _changeState(true)
{
	makeMainMenu();
}

Menu::~Menu()
{
}

void Menu::deselectAll()
{
	for (auto &i : _item) {
		i.deselect();
	}
}

void 	Menu::makeJoinMenu()
{
	_item.clear();
	std::vector<std::wstring> toto;
	toto.push_back(L"Hello");
	toto.push_back(L"there");
	toto.push_back(L"Hello");
	toto.push_back(L"there");
	toto.push_back(L"Hello");
	toto.push_back(L"there");
	toto.push_back(L"Hello");
	toto.push_back(L"there");
	toto.push_back(L"Hello");
	toto.push_back(L"there");
	toto.push_back(L"Hello");
	toto.push_back(L"there");
	toto.push_back(L"Hello");
	toto.push_back(L"there");
	toto.push_back(L"Hello");
	toto.push_back(L"there");
	toto.push_back(L"Hello");
	toto.push_back(L"there");
	toto.push_back(L"Hello");
	toto.push_back(L"there");
	toto.push_back(L"Hello");
	toto.push_back(L"there");
	toto.push_back(L"Hello");
	toto.push_back(L"there");
	toto.push_back(L"Hello");
	toto.push_back(L"there");
	toto.push_back(L"Hello");
	toto.push_back(L"there");
	toto.push_back(L"Hello");
	toto.push_back(L"there");
	toto.push_back(L"Hello");
	toto.push_back(L"there");

	_item.push_back(MenuItem(TypeItem::LISTBOX, 2, "", 500, 250, 600, 400));
	_item[0].setChoices(toto);
	_item.push_back(MenuItem(TypeItem::LABEL, 1, "Select Game to load : ", 500, 150, 600, 100));
	_item.push_back(MenuItem(TypeItem::BUTTON, 3, "Connect", 500, 700, 600, 100));
}

void    Menu::makeOptionMenu()
{
	_item.clear();
	_item.push_back(MenuItem(TypeItem::LABEL, 1, "Number Player : ", 200, 150, 300, 100));
	_item.push_back(MenuItem(TypeItem::BUTTON, 2, "+", 300, 325, 100, 100));
	_item.push_back(MenuItem(TypeItem::LABEL, 3, std::to_string(_nbPlayer), 300, 475, 100, 100));
	_item.push_back(MenuItem(TypeItem::BUTTON, 4, "-", 300, 625, 100, 100));
	_item.push_back(MenuItem(TypeItem::LABEL, 5, "Game name : ", 800, 250, 300, 100));
	_item.push_back(MenuItem(TypeItem::INPUT, 6, "Game1" , 800, 500, 300, 100));
	_item.push_back(MenuItem(TypeItem::BUTTON, 7, "Start Game", 850, 700, 200, 100));
	_item.push_back(MenuItem(TypeItem::LABEL, 8, "", 1250, 0, 820, 1000));
	_item.push_back(MenuItem(TypeItem::CHECKBOX, 9, "", 1400, 200, 50, 50));
	_item.push_back(MenuItem(TypeItem::LABEL, 10, "Bomb Up", 1500, 200, 100, 50));
	_item.push_back(MenuItem(TypeItem::CHECKBOX, 11, "", 1400, 300, 50, 50));
	_item.push_back(MenuItem(TypeItem::LABEL, 12, "Power Up", 1500, 300, 100, 50));
	_item.push_back(MenuItem(TypeItem::CHECKBOX, 13, "", 1400, 400, 50, 50));
	_item.push_back(MenuItem(TypeItem::LABEL, 14, "Penetration", 1500, 400, 100, 50));
	_item.push_back(MenuItem(TypeItem::CHECKBOX, 15, "", 1400, 500, 50, 50));
	_item.push_back(MenuItem(TypeItem::LABEL, 16, "Speed", 1500, 500, 100, 50));
	_item.push_back(MenuItem(TypeItem::CHECKBOX, 17, "", 1400, 600, 50, 50));
	_item.push_back(MenuItem(TypeItem::LABEL, 18, "Wall Pass", 1500, 600, 100, 50));
	_item.push_back(MenuItem(TypeItem::CHECKBOX, 19, "", 1400, 700, 50, 50));
	_item.push_back(MenuItem(TypeItem::LABEL, 20, "Kick", 1500, 700, 100, 50));
}

void    Menu::makeMainMenu()
{
	_item.clear();
	_item.push_back(MenuItem(TypeItem::BUTTON, 1, "Start Game", 500, 280, 500, 100));
	_item.push_back(MenuItem(TypeItem::BUTTON, 2, "Join Game", 500, 430, 500, 100));
	_item.push_back(MenuItem(TypeItem::BUTTON, 3, "Quit", 500, 580, 500, 100));
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
	}
}

static void selectAnother(int before, int after, std::vector<MenuItem> &item)
{
	item[before].deselect();
	item[after].select();
}


static int findSelected(std::vector<MenuItem> &item)
{
	int id = 0;

	for (auto &i : item) {
		if (i.isSelected())
			return id;
		id++;
	}
	return 0; // p-ê renvoyer -1 mais check le renvoi de findSelected
}

void Menu::firstMenuKey(Actions &actions, STATE &state)
{
	if (actions.space || actions.enter || actions.buttonPressed != -1) {
		if (actions.buttonPressed != -1)
			_step = actions.buttonPressed;
		else
			_step = findSelected(_item) + 1;
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

static void actionIsUp(std::vector<MenuItem> &_item)
{
	if (_item[0].isSelected()) {
		_item[_item.size() - 1].select();
		_item[0].deselect();
	} else
		selectAnother(findSelected(_item), findSelected(_item) - 1, _item);
}

static void actionIsDown(std::vector<MenuItem> &_item)
{
	if (static_cast<unsigned int>(findSelected(_item)) == _item.size() - 1) {
		_item[_item.size() - 1].deselect();
		_item[0].select();
	} else
		selectAnother(findSelected(_item), findSelected(_item) + 1, _item);
}

void Menu::handleFirstMenu(Actions &actions, STATE &state)
{
	if (actions.up)
		actionIsUp(_item);
	else if (actions.down)
		actionIsDown(_item);
	else
		firstMenuKey(actions, state);
}

void 	Menu::handleSecondMenu(Actions &actions, STATE &state)
{
	if (actions.escape == true) {
		_change_menu = true;
		_step = 1;
		_changeState = true;
		_changed = true;
	}
	if (actions.buttonPressed == 7)
		state = STATE::GAME;
	else if (actions.buttonPressed == 2) {
		if (_nbPlayer < 4)
			_nbPlayer += 1;
		_item[2].setText(std::to_string(_nbPlayer));
		_changeState = true;
	}
	else if (actions.buttonPressed == 4) {
		if (_nbPlayer > 2)
			_nbPlayer -= 1;
		_item[2].setText(std::to_string(_nbPlayer));
		_changeState = true;
	}
}

void 	Menu::handleThirdMenu(Actions &actions, STATE &state)
{
	if (actions.escape == true) {
		_change_menu = true;
		_changed = true;
		_step = 1;
		return ;
	}
	if (actions.buttonPressed == 2)
		state = STATE::GAME;
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
	if (_step == 2 && actions.buttonPressed == 7) {
		state = STATE::GAME;
		return false;
	}
	if (keyPressed(actions, _changeState)) {
		_changeState = false;
		return true;
	}
	return false;
}

MenuItem &Menu::getItemByID(int id)
{
	return _item[id - 1];
}

std::vector<MenuItem> &Menu::getMenuItems()
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
	}
}