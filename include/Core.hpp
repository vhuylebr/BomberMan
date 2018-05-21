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

enum class GameState {
	NEWGAME,
	LOADGAME
};

struct  parameters
{
	GameState state;                // State si la map doit être à nouveau ou doit être chargée depuis un fichier
	std::wstring gameName;          // Le fichier dans lequel on devra sauvegarde ou get les infos de la map
	int nbPlayers;
	std::pair<int,int> mapSize;
	std::vector<eItem> bonuses;		// Vecteur de bonus actifs
};

class Core {
public:
	Core();
	~Core() = default;

	int loop();
	void menuManager(STATE &last);
	void gameManager(STATE &last);
//	void pauseManager(STATE &last);
	void getParametersFromMenu();


private:
	parameters _param;
	STATE   _state;
	GameCore    _game;
	Menu    _menu;
	IrrLib  _lib;
	char    _host;
	// Lobby   _lobby;
	Actions _act;
};

#endif /* CORE_HPP_ */
