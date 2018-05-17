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
#include <memory>
#include "IEntity.hpp"
#include "MyEventReceiver.hpp"
#include "Actions.hpp"
#include "MenuItem.hpp"

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
		void addCube(std::unique_ptr<IEntity>&);
		Actions getActions();
		bool getRun();
		void createPlane(std::pair<std::size_t, std::size_t> &size);
		void affGameEntities(std::vector<std::unique_ptr<IEntity>>&);
		void affMenuItems(std::vector<MenuItem>&);
		void addButton(const MenuItem &item);
		void addStaticText(const MenuItem &item);
		void addEditBox(const MenuItem &item);
		void addCheckBox(const MenuItem &item);
		void drop();
		void drawMenu();
		int getIdButtonPressed() const;
		std::wstring getInputText(MenuItem &item);
		bool getCheckboxState(MenuItem &item);
		std::wstring getLabelText(MenuItem &item);
		void displayBackground();
		void initGame(std::vector<std::unique_ptr<IEntity>> &gameEntities,
			std::pair<std::size_t, std::size_t> size);
		void drawGame();
		void cleanMenu();

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
		std::map<TypeItem, std::function<void(const MenuItem&)>> _factory;
		std::map<Entity, std::function<void(std::unique_ptr<IEntity>&)>> _gameFactory;
		std::vector<irr::gui::IGUIEditBox*> _inputs;
		std::vector<irr::gui::IGUICheckBox*> _checkboxes;
		std::vector<irr::gui::IGUIStaticText*> _labels;
		irr::scene::ICameraSceneNode	*_camera;
		irr::scene::ISceneNode	*_skybox;
		irr::core::vector3df		_camPos;
};

#endif /* !IRRLIB_HPP_ */
