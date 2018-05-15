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

typedef std::pair<unsigned char, unsigned char> pairUC;

enum class TypeItem {
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
    void setCoord(unsigned char x, unsigned char y);
    void setSize(unsigned char x, unsigned char y);
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
	std::pair<unsigned char, unsigned char> _coord;
	std::pair<unsigned char, unsigned char> _size;
};

#endif /* !MENUITEM_HPP_ */
