#ifndef CORE_HPP_
# define CORE_HPP_

# include "State.hpp"
# include "Actions.hpp"
# include "IrrLib.hpp"
# include "GameCore.hpp"
# include "Menu.hpp"
# include "Item.hpp"


struct t_bonus {
	int id;
	eItem bonus;    
};

class Core {
public:
	Core();
	~Core() = default;

	int 		loop();
	int 		getParametersFromMenu();
	
protected:
	int 		startMusic();
	void 		menuManager(STATE &last);
	void 		gameManager(STATE &last);

private:
	parameters	_param;
	STATE   	_state;
	GameCore    _game;
	Menu    	_menu;
	IrrLib  	_lib;
	char    	_host;
	Music 		_coremusic;
	// Lobby   	_lobby;
	Actions 	_act;
	__int64 	_now;
};

#endif /* CORE_HPP_ */
