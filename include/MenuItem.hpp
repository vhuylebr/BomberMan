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

typedef std::pair<unsigned int, unsigned int> pairUC;

enum class TypeItem {
    BUTTON,
    CHECKBOX,
    INPUT,
    LABEL
};

class MenuItem {
public:
    MenuItem(std::string text = std::string());
    ~MenuItem() {}
    void setText(const std::string &text) { _text = text; }
    void select() { _selected = true; }
    void setCoord(unsigned int x, unsigned int y);
    void setSize(unsigned int x, unsigned int y);
    void setTexture() {}
    void deselect() { _selected = false; }
    bool isSelected() const { return _selected; }
    std::string getText() const { return _text; }
    pairUC getCoord() const { return _coord; }
    pairUC getSize() const { return _size; }
    void setType(TypeItem type) { _type = type; }
    TypeItem getType() const { return _type; }

private:
    TypeItem _type;
    bool _selected;
	std::string _text;
	// texture
	std::pair<unsigned int, unsigned int> _coord;
	std::pair<unsigned int, unsigned int> _size;
};

#endif /* !MENUITEM_HPP_ */
