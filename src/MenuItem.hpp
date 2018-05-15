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

enum class TypeMenuItem {
    INPUT,
    CHECKBOX,
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
    void setType(TypeMenuItem &type) { _type = type; }
    void deselect() { _selected = false; }
    bool isSelected() const { return _selected; }
    std::string getText() const { return _text; }
    pairUC getCoord() const { return _coord; }
    pairUC getSize() const { return _size; }
    TypeMenuItem getType() const { return _type; }

private:
    bool _selected;
	std::string _text;
	// texture
	std::pair<unsigned char, unsigned char> _coord;
	std::pair<unsigned char, unsigned char> _size;
    TypeMenuItem _type;
};

#endif /* !MENUITEM_HPP_ */
