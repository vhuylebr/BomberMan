#ifndef CORE_HPP_
# define CORE_HPP_

# include "State.hpp"
# include "Actions.hpp"
# include "IrrLib.hpp"
# include "GameCore.hpp"
# include "Menu.hpp"
# include "Item.hpp"

struct  parameters
{
    std::pair<int,int> mapSize;
    int nbPlayers;
    std::vector<eItem> bonuses;
    std::wstring gameName;
};


class Core {
public:
    Core();
    ~Core() = default;

    int loop();
    void menuManager(STATE &last);
    // void lobbyManager(STATE &last);
    void gameManager(STATE &last);
    void  getParameters();

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
