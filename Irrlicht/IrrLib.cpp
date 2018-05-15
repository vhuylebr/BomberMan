/*
** EPITECH PROJECT, 2018
** irrlicht
** File description:
** irrlicht
*/

#include "IrrLib.hpp"

IrrLib::IrrLib(Actions &KeyIsDown)
	:_actions(KeyIsDown)
{
	_device = createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1920, 1080),
		16, false, false, false, &_eventReceiver);
	_device->setWindowCaption(L"Irrlicht Engine - User Interface");
	_device->setResizable(false);
	_driver = _device->getVideoDriver();
	_smgr = _device->getSceneManager();
	_guienv = _device->getGUIEnvironment();
	_geomentryCreator = _smgr->getGeometryCreator();
	_factory.insert(std::make_pair(TypeItem::INPUT, std::bind(&IrrLib::addEditBox, this,
		std::placeholders::_1)));
	_factory.insert(std::make_pair(TypeItem::CHECKBOX, std::bind(&IrrLib::addCheckBox, this,
		std::placeholders::_1)));
	_factory.insert(std::make_pair(TypeItem::LABEL, std::bind(&IrrLib::addStaticText, this,
		std::placeholders::_1)));
	_factory.insert(std::make_pair(TypeItem::BUTTON, std::bind(&IrrLib::addButton, this,
		std::placeholders::_1)));
}

IrrLib::~IrrLib()
{
}

void IrrLib::createPlane()
{
	irr::scene::IMesh* plane = _geomentryCreator->createPlaneMesh(irr::core::dimension2d<irr::f32>(5, 5),
		irr::core::dimension2d<irr::u32>(5, 5));
	irr::scene::ISceneNode* ground = _smgr->addMeshSceneNode(plane);
	ground->setPosition(irr::core::vector3df(0, 0, 0));
	ground->setMaterialTexture(0, _driver->getTexture("../media/grass.bmp"));
	ground->setMaterialFlag(irr::video::EMF_LIGHTING, false);    //This is important
}

void IrrLib::addCube(double x, double y)
{
	irr::scene::ISceneNode* cube = _smgr->addCubeSceneNode(1);
	cube->setPosition(irr::core::vector3df(x, 0.5, y));
	cube->setMaterialTexture(0, _driver->getTexture("../media/wall.bmp"));
	cube->setMaterialFlag(irr::video::EMF_LIGHTING, false);    //This is important
	cube->render();
	_cubes.push_back(cube);
}

void IrrLib::addCube(irr::core::vector3df pos)
{
	irr::scene::ISceneNode* cube = _smgr->addCubeSceneNode(1);
	cube->setPosition(pos);
	cube->setMaterialTexture(0, _driver->getTexture("../media/wall.bmp"));
	cube->setMaterialFlag(irr::video::EMF_LIGHTING, false);    //This is important
	cube->render();
	_cubes.push_back(cube);
}

Actions	IrrLib::getActions()
{
	_actions.escape = false;
	_actions.space = false;
	_actions.right = false;
	_actions.left = false;
	_actions.up = false;
	_actions.down = false;
	if (_eventReceiver.IsKeyDown(irr::KEY_LEFT))
		_actions.left = true;
	if (_eventReceiver.IsKeyDown(irr::KEY_RIGHT))
		_actions.right = true;
	if (_eventReceiver.IsKeyDown(irr::KEY_UP))
		_actions.up = true;
	if (_eventReceiver.IsKeyDown(irr::KEY_DOWN))
		_actions.down = true;
	if (_eventReceiver.IsKeyDown(irr::KEY_ESCAPE))
		_actions.escape = true;
	if (_eventReceiver.IsKeyDown(irr::KEY_SPACE))
		_actions.space = true;
	return (_actions);
}

void IrrLib::addButton(const MenuItem &item)
{	
	std::wstring wText;
	std::string str = item.getText();

	for (unsigned int i = 0; i < str.size(); ++i)
		wText += wchar_t(str[i]);
	irr::gui::IGUIButton *button = _guienv->addButton(irr::core::rect<irr::s32>(item.getCoord().first,
		item.getCoord().second, item.getCoord().first + item.getSize().first,
			item.getCoord().second + item.getSize().second), 0, GUI_ID_QUIT_BUTTON,
				wText.c_str());
	button->setPressed(item.isSelected());
}

void IrrLib::addStaticText(const MenuItem &item)
{
	std::wstring wText;
	std::string str = item.getText();

	for (unsigned int i = 0; i < str.size(); ++i)
		wText += wchar_t(str[i]);
	_guienv->addStaticText(wText.c_str(), irr::core::rect<irr::s32>(item.getCoord().first,
		item.getCoord().second, item.getCoord().first + item.getSize().first,
			item.getCoord().second + item.getSize().second), true);
}

void IrrLib::addEditBox(const MenuItem &item)
{
	std::wstring wText;
	std::string str = item.getText();

	for (unsigned int i = 0; i < str.size(); ++i)
		wText += wchar_t(str[i]);
	_guienv->addEditBox(wText.c_str(), irr::core::rect<irr::s32>(item.getCoord().first,
		item.getCoord().second, item.getCoord().first + item.getSize().first,
			item.getCoord().second + item.getSize().second));
}

void IrrLib::addCheckBox(const MenuItem &item)
{
	std::wstring wText;
	std::string str = item.getText();

	for (unsigned int i = 0; i < str.size(); ++i)
		wText += wchar_t(str[i]);
	_guienv->addCheckBox(false, irr::core::rect<irr::s32>(item.getCoord().first,
		item.getCoord().second, item.getCoord().first + item.getSize().first,
			item.getCoord().second + item.getSize().second));
}

bool IrrLib::getRun()
{
	return _device->run();
}

void IrrLib::affMenuItems(std::vector<MenuItem> menuItems)
{
	_driver->beginScene(true, true, irr::video::SColor(0,100,100,100));
	for (auto it = menuItems.begin(); it != menuItems.end(); ++it) {
		_factory[it->getType()](*it);
	}
	_guienv->drawAll();
	_driver->endScene();
}

void IrrLib::drop()
{
	_device->drop();
}
// void IrrLib::AffEntities(std::vector<GameEntities> entities)
// {
	
// }