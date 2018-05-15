/*
** EPITECH PROJECT, 2018
** Indie Studio
** File description:
** Menu
*/

#include "Menu.hpp"
#include <iostream>


Menu::Menu()
	: _step(1), _nb_player(4), _change_menu(true), _changeState(true)
{
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
		MenuItem("Kick"),
	};
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

void 	Menu::makeJoinMenu()
{
	MenuItem tmp;

	_item.clear();
	tmp.setType(TypeItem::INPUT);
	tmp.setCoord(950, 150);
	tmp.setSize(350, 100);
	tmp.setText("Enter your IP here");
	_item.push_back(tmp);
	tmp.setCoord(950, 350);
	tmp.setText("Enter your Username here");
	_item.push_back(tmp);
	tmp.setType(TypeItem::BUTTON);
	tmp.setCoord(950, 550);
	tmp.setText("Connect");
	_item.push_back(tmp);
	tmp.setType(TypeItem::LABEL);
	tmp.setCoord(350, 150);
	tmp.setText("IP : ");
	_item.push_back(tmp);
	tmp.setCoord(350, 350);
	tmp.setText("Pseudo : ");
	_item.push_back(tmp);
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
	tmp.setText("3");
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
}

static void attributeId(std::vector<MenuItem> &item)
{
	int id = 1;

	for (auto &i : item) {
		i.setId(id);
		id++;
	}
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
	if (actions.space) {// ou Enter 
		// gérer le clic et changé le selectionné si l'on a cliqué ailleurs
		_step = findSelected(_item) + 1;
		// std::cout << "step is : " << _step << std::endl;
		if (_step == 2)
			_step = 3; // Join a Game;
		if (_step == 1)
			_step = 2; // Create new Game
		if (_step == 4)
			state = STATE::EXIT;
		_change_menu = true;
		_changeState = true;
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
	if (actions.up) {
		actionIsUp(_item);
		_changeState = true;
	}
	else if (actions.down) {
		actionIsDown(_item);
		_changeState = true;
	}
	else
		firstMenuKey(actions, state);
}

void 	Menu::handleThirdMenu(Actions &actions, STATE &state)
{
	// std::cout << "je passe bien par ici" << std::endl;
}

bool 	Menu::changeState()
{
	if (_changeState == true) {
		// std::cout << "je passe bien ici val" << std::endl;
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
			// std::cout << "on verra ça après ok" << std::endl;
//			handleSecondMenu(actions, state);
			break;
		case 3:
			handleThirdMenu(actions, state);
			break;
	}
	clearAction(actions);
	return _item;
}