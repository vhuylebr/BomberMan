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
#include "MyEventReceiver.hpp"
#include "../src/Actions.hpp"

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
		void AffEntities(std::vector<Entities>);

	private:
		irr::IrrlichtDevice		*_device;
		irr::video::IVideoDriver	*_driver;
		irr::scene::ISceneManager	*_smgr;
		irr::gui::IGUIEnvironment	*_guienv;
		MyEventReceiver			_eventReceiver;
		const irr::scene::IGeometryCreator *_geomentryCreator;
		std::vector<irr::scene::ISceneNode*> _cubes;
		Actions _actions;
};

#endif /* !IRRLIB_HPP_ */
