/*
** EPITECH PROJECT, 2018
** Indie studio
** File description:
** Menu header
*/

#ifndef MENU_HPP_
# define MENU_HPP_

# include <vector>
# include "Actions.hpp"
# include "MenuItem.hpp"
# include "Item.hpp"

class Menu {
public:
    Menu();
    ~Menu();
    std::vector<MenuItem> &getMenu(char &to_write, Actions &actions);
    bool isHost() const;
    std::string getIP() const { return _ip; }
    std::string getPseudo() const { return _pseudo; }
    std::vector<eItem> &getBonus() { return _bonus; }
    unsigned char getNbPlayer() const { return _nb_player; }

private:
    void makeMainMenu();
    void makeOptionMenu();
    void makeJoinMenu();
    unsigned char _step;
    unsigned char _nb_player;
    std::string _pseudo;
    std::string _ip;
    std::vector<eItem> _bonus;
    std::vector<MenuItem> _item;
	//menu1: titre, "start game", "join game", "quit"
	//menu2: nb_p, pseudo, liste de bonus, quit
	//menu3: pseudo, ip, quit
};

#endif /* !MENU_HPP_ */
