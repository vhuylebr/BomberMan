/*
** EPITECH PROJECT, 2018
** Indie studio
** File description:
** MenuItem class
*/

#ifndef MENUITEM_HPP_
# define MENUITEM_HPP_

# include <utility>
# include <string>
# include <vector>
# include "IEntity.hpp"

typedef std::pair<std::size_t, std::size_t> pairUC;

using ui = unsigned int;

class MenuItem : public IEntity {
public:
    MenuItem(std::string text = std::string());
    MenuItem(Entity type, int id, std::string text, ui x, ui y, ui lenght, ui height);
    ~MenuItem() {}
    void setText(const std::string &text) { _text = text; }
    void select() { _selected = true; }
    void setCoord(unsigned int x, unsigned int y);
    void setSize(unsigned int x, unsigned int y);
    void setChoices(std::vector<std::wstring> choices) { _choices = choices; };
    void setTexture() {}
    void deselect() { _selected = false; }
    bool isSelected() const { return _selected; }
    std::string getText() const { return _text; }
    pairUC getPos() const { return _coord; }
    pairUC getSize() const { return _size; }
    void setType(Entity type) { _type = type; }
    Entity getType() const { return _type; }
    std::vector<std::wstring> getChoices() const { return _choices; }
    void setId(int id) { _id = id; }
    int getId() const { return _id; }

private:
    Entity _type;
    int _id;
    std::string _text;
    std::pair<std::size_t, std::size_t> _coord;
    std::pair<std::size_t, std::size_t> _size;
    bool _selected;
    std::vector<std::wstring> _choices;
};

#endif /* !MENUITEM_HPP_ */
