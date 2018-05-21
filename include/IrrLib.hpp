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
#include "Player.hpp"
#include "ACube.hpp"

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
		void addPlayer(std::unique_ptr<IEntity> &);
		void addSphere(std::unique_ptr<IEntity> &entity);
		void updateSphere(std::unique_ptr<IEntity> &entity);
		
		Actions getActions();
		bool getRun();
		void createPlane(pairUC &size);
		void affGameEntities(std::vector<std::unique_ptr<IEntity>>&);
		
		// void affMenuItems(std::vector<MenuItem>&);
		void addButton(std::unique_ptr<IEntity>&);
		void addStaticText(std::unique_ptr<IEntity>&);
		void addEditBox(std::unique_ptr<IEntity>&);
		void addCheckBox(std::unique_ptr<IEntity>&);
		void addListBox(std::unique_ptr<IEntity>&);
		
		std::wstring getInputText(std::unique_ptr<IEntity> &item);
		bool getCheckboxState(std::unique_ptr<IEntity> &item);
		std::wstring getLabelText(std::unique_ptr<IEntity> &item);
		void initMenu(std::vector<std::unique_ptr<IEntity>> &);
		void updateLabel(std::unique_ptr<IEntity>&);
		
		void drop();
		void drawMenu();
		int getIdButtonPressed() const;
		std::wstring getListBoxChoice(std::unique_ptr<IEntity>&);
		void displayBackground();
		void initGame(std::vector<std::unique_ptr<IEntity>> &gameEntities,
			pairUC size);
		void drawGame();
		void cleanMenu();
		void initMenu(std::vector<MenuItem> &);
		void updateLabel(MenuItem &item);
		void updatePlayer(std::unique_ptr<IEntity> &entity);
		void updateCube(std::unique_ptr<IEntity> &entity);
		
		// void addStaticText(std::unique_ptr<IEntity> &item);
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
		std::map<Entity, std::function<void(std::unique_ptr<IEntity>&)>> _factory;
		std::vector<irr::gui::IGUIEditBox*> _inputs;
		std::vector<irr::gui::IGUICheckBox*> _checkboxes;
		std::vector<irr::gui::IGUIStaticText*> _labels;
		irr::gui::IGUIListBox *_listbox;
		irr::scene::ICameraSceneNode	*_camera;
		irr::scene::ISceneNode	*_skybox;
		irr::core::vector3df		_camTarget;
		irr::scene::ISceneNode* _ground;
		std::vector<irr::scene::IAnimatedMeshSceneNode*> _players;
		std::map<Entity, std::function<void(std::unique_ptr<IEntity>&)>> _factoryUpdate;
		std::vector<irr::scene::ISceneNode*> _spheres;
};

#endif /* !IRRLIB_HPP_ */
