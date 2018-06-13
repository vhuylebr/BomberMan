/*
** EPITECH PROJECT, 2018
** Indie studio
** File description:
** Menu header
*/

#ifndef MENU_HPP_
# define MENU_HPP_

# include <ctime>
# include <vector>
# include <map>
# include <memory>
# include <algorithm>
# include "Actions.hpp"
# include "MenuItem.hpp"
# include "Item.hpp"
# include "State.hpp"
# include "Metrics.hpp"
# include "Map.hpp"

class Menu {
public:
	Menu();
	~Menu();

	void 									getMenu(Actions &actions, STATE &state);
	bool 									isHost() const;
	void 									deselectAll();
	std::string 							getIP() const { return _ip; }
	std::string 							getPseudo() const { return _pseudo; }
	unsigned char 							getNbPlayer() const { return _nbPlayer; }
	int 									getNbBots() const { return _nbBots; }
	std::vector<std::unique_ptr<IEntity>> 	&getMenuItems();
	void 									changeMenu();
	bool 									getState(Actions &actions, STATE &state);
	std::vector<eItem> 						&getBonus();
	std::unique_ptr<IEntity> 				&getItemByID(int);
	bool 									stepChanged(STATE &state);
	int 									getStep() const { return _step;}
	void 									makeModeMenu();
	Map 									getMap() const { return _map; }
	bool 									isLabelToUpdate() { if (_changeState) { _changeState = false; return true; } return false; }
	std::vector<int> 						getIdToUpdate(const Actions &actions);
	int 									getMapSize() const { return _sizeMap; }

private:
	std::clock_t _start;
	void makeIntroMenu();
	void handleIntroMenu(Actions &);
	void 									rotateMaps(bool left);
	void 									handleModeMenu(Actions &actions, STATE &state);
	void 									firstMenuKey(Actions &actions, STATE &state);
	void 									checkBonus(Actions &actions);
	void 									handleFirstMenu(Actions &actions, STATE &state);
	void		 							handleSecondMenu(Actions &actions, STATE &state);
	void 									handleThirdMenu(Actions &actions, STATE &state);
	void 									handleMapMenu(Actions &actions, STATE &state);
	void 									handleParamsMenu(Actions &actions, STATE &state);

	void				 					initMaps();
	void 									makeParamsMenu();
	void 									makeMainMenu();
	void 									makeJoinMenu();
	void 									makeMapMenu();

	int 									_idToUpdate;
	bool 									_randomMode;
	int 									_nbBotsMax;
	int 									_step;
	int 									_nbPlayer;
	int 									_nbBots;
	int 									_sizeMap;
	int 									_mapH;
	int 									_mapW;
	bool 									_change_menu;
	Map 									_map;
	std::string 							_pseudo;
	std::string 							_ip;
	std::map<eItem, bool> 					_map_bonus;
	std::vector<Map> 						_maps;
	std::vector<std::unique_ptr<IEntity>> 	_item;
	std::vector<eItem> 						_bonus;
	int     								_changeState;
	bool 									_changed;
};

#endif /* !MENU_HPP_ */
