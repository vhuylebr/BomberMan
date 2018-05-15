/*
** EPITECH PROJECT, 2018
** Indie Studio
** File description:
** Menu
*/

#include "Menu.hpp"

Menu::Menu()
    : _step(1), _nb_player(4), _change_menu(true)
{
    makeMainMenu();
}

Menu::~Menu()
{
}

static void addItemList(std::vector<MenuItem> &item)
{
    MenuItem bonus[NB_ITEMS] = 
    {   MenuItem("Bomb Up"),
        MenuItem("Power Up"),
        MenuItem("Penetration"), // Peut-être renommer ça en "Super Bomb"
        MenuItem("Speed"),
        MenuItem("Wall Pass"),
        MenuItem("Kick"),
    };
    for (int i = 0; i < NB_ITEMS; i++) {
        bonus[i].setCoord(180, ((i + 1) * 30));
        bonus[i].setSize(60, 20);
        item.push_back(bonus[i]);
    }
}

void Menu::deselectAll()
{
    for (auto &i : _item) {
        i.deselect();
    }
}

void    Menu::makeOptionMenu()
{
    MenuItem tmp;

    _item.clear();
    tmp.setText("Quit");
    tmp.setCoord(20, 90);
    tmp.setSize(40, 20);
    _item.push_back(tmp);
    tmp.setText("Pseudo");
    tmp.setCoord(80, 60);
    tmp.setSize(60, 20);
    _item.push_back(tmp);
    tmp.setText("Number player");
    tmp.setCoord(80, 120);
    tmp.setSize(60, 20);
    _item.push_back(tmp);
    tmp.setText(std::to_string(_nb_player));
    tmp.setCoord(80, 120);
    tmp.setSize(60, 20);
    _item.push_back(tmp);
    addItemList(_item);
}

void    Menu::makeMainMenu()
{
    MenuItem tmp;

    _item.clear();
    tmp.setType(TypeItem::INPUT);
    tmp.setText("Start game");
    tmp.select();
    tmp.setCoord(60, 40);
    tmp.setSize(80, 20);
    _item.push_back(tmp);
    tmp.deselect();
    tmp.setText("Join game");
    tmp.setCoord(60, 80);
    tmp.setSize(80, 20);
    _item.push_back(tmp);
    tmp.setText("Quit");
    tmp.setCoord(60, 120);
    tmp.setSize(80, 20);
    _item.push_back(tmp);
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
            // makeJoinMenu();
            break;
    }
}

std::vector<MenuItem> &Menu::getMenu(char &to_write, Actions &actions, STATE &state)
{
    if (_change_menu == true)
        changeMenu();
    (void)to_write;
    (void)actions;
    (void)state;
    return _item;
}