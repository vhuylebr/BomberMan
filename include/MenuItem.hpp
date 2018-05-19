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

typedef std::pair<unsigned int, unsigned int> pairUC;

enum class TypeItem {
    BUTTON,
    CHECKBOX,
    INPUT,
    LABEL,
    LISTBOX
};

using ui = unsigned int;

class MenuItem {
public:
    MenuItem(std::string text = std::string());
    MenuItem(TypeItem type, int id, std::string text, ui x, ui y, ui lenght, ui height);
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
    pairUC getCoord() const { return _coord; }
    pairUC getSize() const { return _size; }
    std::vector<std::wstring> getChoices() const { return _choices; }
    void setType(TypeItem type) { _type = type; }
    TypeItem getType() const { return _type; }
    void setId(int id) { _id = id; }
    int getId() const { return _id; }

private:
    TypeItem _type;
    int _id;
    std::string _text;
    std::pair<unsigned int, unsigned int> _coord;
    std::pair<unsigned int, unsigned int> _size;
    bool _selected;
    std::vector<std::wstring> _choices;
};

#endif /* !MENUITEM_HPP_ */
