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
	_device = createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1600, 900),
		16, false, false, false, &_eventReceiver);
	_device->setWindowCaption(L"Irrlicht Engine - User Interface");
	_device->setResizable(false);
	_driver = _device->getVideoDriver();
	_smgr = _device->getSceneManager();
	_camera = _smgr->addCameraSceneNode();
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
	_gameFactory.insert(std::make_pair(Entity::WALL, std::bind(&IrrLib::addCube, this,
		std::placeholders::_1)));
	_skybox = _smgr->addSkyBoxSceneNode(
		_driver->getTexture("./media/mp_classm/classmplanet_up.tga"),
		_driver->getTexture("./media/mp_classm/classmplanet_dn.tga"),
		_driver->getTexture("./media/mp_classm/classmplanet_rt.tga"),
		_driver->getTexture("./media/mp_classm/classmplanet_lf.tga"),
		_driver->getTexture("./media/mp_classm/classmplanet_ft.tga"),
		_driver->getTexture("./media/mp_classm/classmplanet_bk.tga"));
	_skybox->setVisible(false);
	_camPos = irr::core::vector3df(10, 20, 10);
	_camera->setPosition(_camPos);
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
	ground->setMaterialTexture(0, _driver->getTexture("./media/grass.bmp"));
	ground->setMaterialFlag(irr::video::EMF_LIGHTING, false);    //This is important
}

void IrrLib::addCube(std::unique_ptr<IEntity> &entity)
{
	irr::scene::ISceneNode* cube = _smgr->addCubeSceneNode(1);
	cube->setPosition(irr::core::vector3df(entity->getPos().first, 0.5, entity->getPos().second));
	cube->setMaterialTexture(0, _driver->getTexture("./media/wall.bmp"));
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
	_actions.enter = false;
	_actions.buttonPressed = getIdButtonPressed();
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
	if (_eventReceiver.IsKeyDown(irr::KEY_RETURN))
		_actions.enter = true;
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
			item.getCoord().second + item.getSize().second), 0, item.getId(),
				wText.c_str());
	button->setPressed(item.isSelected());
	button->setDrawBorder(true);
}

void IrrLib::addStaticText(const MenuItem &item)
{
	std::wstring wText;
	std::string str = item.getText();

	for (unsigned int i = 0; i < str.size(); ++i)
		wText += wchar_t(str[i]);
	_guienv->addStaticText(wText.c_str(), irr::core::rect<irr::s32>(item.getCoord().first,
		item.getCoord().second, item.getCoord().first + item.getSize().first,
			item.getCoord().second + item.getSize().second), item.isSelected());
}

void IrrLib::addEditBox(const MenuItem &item)
{
	std::wstring wText;
	std::string str = item.getText();

	for (unsigned int i = 0; i < str.size(); ++i)
		wText += wchar_t(str[i]);
	irr::gui::IGUIEditBox *editbox = _guienv->addEditBox(wText.c_str(), irr::core::rect<irr::s32>(item.getCoord().first,
		item.getCoord().second, item.getCoord().first + item.getSize().first,
			item.getCoord().second + item.getSize().second));
	editbox->setID(item.getId());
	_inputs.push_back(editbox);
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

void IrrLib::displayBackground()
{
	_camPos.rotateXZBy(-0.2, irr::core::vector3df(20, 20, 20));
	_camera->setTarget(_camPos);
	_camera->setRotation(_camPos);
}

void IrrLib::affMenuItems(std::vector<MenuItem> &menuItems)
{
	_guienv->clear();
	_eventReceiver.resetIdButtonPressed();
	irr::gui::IGUISkin* skin = _guienv->getSkin();
	irr::gui::IGUIFont* font = _guienv->getFont("./media/fontlucida.png");
	skin->setFont(_guienv->getBuiltInFont(), irr::gui::EGDF_TOOLTIP);
	if (font)
		skin->setFont(font);
	else
		std::cout << "font not set" << std::endl;
	for (auto &it : menuItems) {
		_factory[it.getType()](it);
	}
}

std::wstring IrrLib::getInputText(MenuItem &item)
{
	for (auto it = _inputs.begin(); it != _inputs.end(); ++it) {
		if ((*it)->getID() == item.getId()) {
			return ((*it)->getText());
		}
	}
	return (L"");
}

int IrrLib::getIdButtonPressed() const
{
	return _eventReceiver.getIdButtonPressed();
}

void IrrLib::drawMenu()
{
	if (_device->isWindowActive()) {
		_driver->beginScene(true, true);
		_smgr->drawAll();
		_guienv->drawAll();
		_driver->endScene();
	}
}

void IrrLib::initGame(std::vector<std::unique_ptr<IEntity>> &gameEntities)
{
	createPlane();
	for (auto &it : gameEntities) {
		_gameFactory[it->getType()](it);
	}
}

void IrrLib::affGameEntities(std::vector<std::unique_ptr<IEntity>> &gameEntities)
{
	for (auto &it : gameEntities) {//.begin(); it != gameEntities.end(); ++it) {
		_gameFactory[it->getType()](it);
	}
}

void IrrLib::drop()
{
	_device->drop();
}
