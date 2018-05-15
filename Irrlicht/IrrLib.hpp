/*
** EPITECH PROJECT, 2018
** irrlicht
** File description:
** irrlicht
*/

#ifndef IRRLIB_HPP_
	#define IRRLIB_HPP_

#include <irrlicht.h>
#include <vector>
#include <map>
#include <functional>
#include "MyEventReceiver.hpp"
#include "../src/Actions.hpp"
#include "../src/MenuItem.hpp"

enum
{
	GUI_ID_QUIT_BUTTON = 101,
	GUI_ID_NEW_WINDOW_BUTTON,
	GUI_ID_FILE_OPEN_BUTTON,
	GUI_ID_TRANSPARENCY_SCROLL_BAR
};

class IrrLib {
	public:
		IrrLib(Actions &);
		~IrrLib();
		void addCube(double x, double y);
		void addCube(irr::core::vector3df pos);
		Actions getAction();
		void getRun();
		void createPlane();
		void AffMenuItems(std::vector<MenuItem>);
		void addButton(const MenuItem &item);
		void addStaticText(const MenuItem &item);
		void addEditBox(const MenuItem &item);
		void addCheckBox(const MenuItem &item);
		
		// void AffEntities(std::vector<GameEntities>);

	private:
		irr::IrrlichtDevice		*_device;
		irr::video::IVideoDriver	*_driver;
		irr::scene::ISceneManager	*_smgr;
		irr::gui::IGUIEnvironment	*_guienv;
		MyEventReceiver			_eventReceiver;
		const irr::scene::IGeometryCreator *_geomentryCreator;
		std::vector<irr::scene::ISceneNode*> _cubes;
		Actions _actions;
		std::map<TypeMenuItem, std::function<void(const MenuItem&)>> _factory;
};

#endif /* !IRRLIB_HPP_ */
