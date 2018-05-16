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
	_map_bonus[eItem::BOMB_UP] = true;
	_map_bonus[eItem::POWER_UP] = true;
	_map_bonus[eItem::SUPER_BOMB] = true;
	_map_bonus[eItem::SPEED] = true;
	_map_bonus[eItem::BOMB_UP] = true;
	_map_bonus[eItem::BOMB_UP] = true;

	makeMainMenu();
}

Menu::~Menu()
{
}

static void addItemList(std::vector<MenuItem> &item)
{
	MenuItem tmp;
	MenuItem bonus[NB_ITEMS] =
	{   MenuItem("Bomb Up"),
		MenuItem("Power Up"),
		MenuItem("Penetration"), // Peut-être renommer ça en "Super Bomb"
		MenuItem("Speed"),
		MenuItem("Wall Pass"),
		MenuItem("Kick")
	};
	// c'est la ligne de séparation ?
	tmp.setType(TypeItem::LABEL);
	tmp.setCoord(1250, 0);
	tmp.setSize(820, 1080);
	item.push_back(tmp);

	for (int i = 0; i < NB_ITEMS; i++) {
		tmp.setType(TypeItem::CHECKBOX);
		tmp.setCoord(1400, (i + 1) * 100 + 100 );
		tmp.setSize(50, 50);
		item.push_back(tmp);

		bonus[i].setType(TypeItem::LABEL);
		bonus[i].setCoord(1500, ((i + 1) * 100 + 100));
		bonus[i].setSize(100, 50);
		item.push_back(bonus[i]);
	}
}

void Menu::deselectAll()
{
	for (auto &i : _item) {
		i.deselect();
	}
}

static void attributeId(std::vector<MenuItem> &item)
{
	int id = 1;

	for (auto &i : item) {
		i.setId(id);
		id++;
	}
}

void 	Menu::makeJoinMenu()
{
	MenuItem tmp;

	_item.clear();
	tmp.setType(TypeItem::INPUT);
	tmp.select();
	tmp.setCoord(950, 150);
	tmp.setSize(350, 100);
	tmp.setText("Enter your IP here");
	_item.push_back(tmp);
	tmp.setCoord(950, 350);
	tmp.setText("Enter your Username here");
	tmp.deselect();
	_item.push_back(tmp);
	tmp.setType(TypeItem::BUTTON);
	tmp.setCoord(950, 550);
	tmp.setText("Connect");
	tmp.deselect();
	_item.push_back(tmp);
	tmp.setType(TypeItem::LABEL);
	tmp.setCoord(350, 150);
	tmp.setText("IP : ");
	tmp.select();
	_item.push_back(tmp);
	tmp.setCoord(350, 350);
	tmp.setText("Pseudo : ");
	tmp.select();
	_item.push_back(tmp);
	attributeId(_item);
}

void    Menu::makeOptionMenu()
{
	MenuItem tmp;

	// Number Player
	_item.clear();
	tmp.setType(TypeItem::LABEL);
	tmp.setCoord(200, 150);
	tmp.setSize(300, 100);
	tmp.setText("Number Player : ");
	_item.push_back(tmp);

	// +
	tmp.setType(TypeItem::BUTTON);
	tmp.setCoord(300, 325);
	tmp.setSize(100, 100);
	tmp.setText("+");
	_item.push_back(tmp);

	// Number Player effectif
	tmp.setType(TypeItem::LABEL);
	tmp.setCoord(300, 475);
	tmp.setSize(100, 100);
	tmp.setText(std::to_string(_nbPlayer));
	_item.push_back(tmp);

	// -
	tmp.setType(TypeItem::BUTTON);
	tmp.setCoord(300, 625);
	tmp.setSize(100, 100);
	tmp.setText("-");
	_item.push_back(tmp);

	// Pseudo text
	tmp.setType(TypeItem::LABEL);
	tmp.setCoord(800, 250);
	tmp.setSize(300, 100);
	tmp.setText("Pseudo : ");
	_item.push_back(tmp);

	// Pseudo input
	tmp.setType(TypeItem::INPUT);
	tmp.setCoord(800, 500);
	tmp.setSize(300, 100);
	tmp.setText("valerian t'es un pd");
	_item.push_back(tmp);

	// Quit
	tmp.setType(TypeItem::BUTTON);
	tmp.setCoord(850, 700);
	tmp.setSize(200, 100);
	tmp.setText("Quit");
	_item.push_back(tmp);
	addItemList(_item);
	attributeId(_item);
}

void    Menu::makeMainMenu()
{
	MenuItem tmp;

	_item.clear();
	tmp.select();
	tmp.setType(TypeItem::BUTTON);
	tmp.setText("Start game");
	tmp.setCoord(500, 280);
	tmp.setSize(500, 100);
	_item.push_back(tmp);
	tmp.deselect();
	tmp.setText("Join game");
	tmp.setCoord(500, 430);
	_item.push_back(tmp);
	tmp.setText("Quit");
	tmp.setCoord(500, 580);
	_item.push_back(tmp);
	attributeId(_item);
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
	if (actions.space || actions.enter || actions.buttonPressed != -1) { // gérer le clic et changé le selectionné si l'on a cliqué ailleurs
		if (actions.buttonPressed != -1)
			_step = actions.buttonPressed;
		else
			_step = findSelected(_item) + 1;
		if (_step == 3)
			state = STATE::EXIT;
		if (_step == 2)
			_step = 3; // Join a Game;
		if (_step == 1)
			_step = 2; // Create new Game
		if (_step == 4)
			state = STATE::EXIT;
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

static void fillBonus(std::map<eItem, bool> map_bonus, std::vector<eItem> &bnus)
{
	for (auto &i : map_bonus) {
		if (i.second)
			bnus.push_back(i.first);
	}
}

std::vector<eItem> &Menu::getBonus()
{
	fillBonus(_map_bonus, _bonus);
	return _bonus;
}

void Menu::checkBonus(Actions &actions)
{
	if (_step != 2)
		return;
	switch (actions.buttonPressed) {
		case 9:
			_map_bonus[eItem::BOMB_UP] = true;
			break;
		case 11:
			_map_bonus[eItem::POWER_UP] = true;
			break;
		case 13:
			_map_bonus[eItem::SUPER_BOMB] = true;
			break;
		case 15:
			_map_bonus[eItem::SPEED] = true;
			break;
		case 17:
			_map_bonus[eItem::BOMB_UP] = true;
			break;
		case 19:
			_map_bonus[eItem::BOMB_UP] = true;
	}
}

void 	Menu::handleSecondMenu(Actions &actions, STATE &state)
{
	if (actions.buttonPressed == 7)
		state = STATE::EXIT; // Faire la connexion
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
	checkBonus(actions);
	// for (auto &i : _item) {
	// 	if (i.getType() != TypeItem::CHECKBOX)
	// 		std::cout << i.getText() << " = " << i.getId() << std::endl;
	// }
}

void 	Menu::handleThirdMenu(Actions &actions, STATE &state)
{
	if (actions.buttonPressed == 3)
		state = STATE::EXIT; // Faire la connexion
}

bool 	Menu::getState(char &to_write, Actions &actions, STATE &state)
{
	if (actions.buttonPressed != -1 || actions.enter || actions.space || actions.up || actions.down || _changeState == true) {
		_changeState = false;
		return true;
	}
	return false;
}

std::vector<MenuItem> &Menu::getMenu(char &to_write, Actions &actions, STATE &state)
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
	clearAction(actions);
	return _item;
}