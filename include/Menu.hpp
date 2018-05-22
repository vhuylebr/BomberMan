/*
** EPITECH PROJECT, 2018
** Indie studio
** File description:
** Menu header
*/

#ifndef MENU_HPP_
# define MENU_HPP_

# include <vector>
# include <map>
# include <memory>
# include "Actions.hpp"
# include "MenuItem.hpp"
# include "Item.hpp"
# include "State.hpp"

class Menu {
public:
	Menu();
	~Menu();
	void getMenu(Actions &actions, STATE &state);
	bool isHost() const;
	void deselectAll();
	std::string getIP() const { return _ip; }
	std::string getPseudo() const { return _pseudo; }
	unsigned char getNbPlayer() const { return _nbPlayer; }
	std::vector<std::shared_ptr<IEntity>> &getMenuItems();
	void changeMenu();
	bool getState(Actions &actions, STATE &state);
	std::vector<eItem> &getBonus();
	std::shared_ptr<IEntity> &getItemByID(int);
	bool 	stepChanged(STATE &state);
	int getStep() const {return _step;};


private:
	void firstMenuKey(Actions &actions, STATE &state);
	void checkBonus(Actions &actions);
	void handleFirstMenu(Actions &actions, STATE &state);
	void handleSecondMenu(Actions &actions, STATE &state);
	void handleThirdMenu(Actions &actions, STATE &state);

	void makeMainMenu();
	void makeOptionMenu();
	void makeJoinMenu();

	int _step;
	int _nbPlayer;
	bool _change_menu;
	std::string _pseudo;
	std::string _ip;
	std::map<eItem, bool> _map_bonus;
	std::vector<std::shared_ptr<IEntity>> _item;
	std::vector<eItem> _bonus;
	int     _changeState;
	bool 	_changed;
	//menu1: titre, "start game", "join game", "quit"
	//menu2: nb_p, pseudo, liste de bonus, quit
	//menu3: pseudo, ip, quit
};

#endif /* !MENU_HPP_ */
