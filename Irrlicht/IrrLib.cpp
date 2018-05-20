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
	_factory.insert(std::make_pair(Entity::INPUT, std::bind(&IrrLib::addEditBox, this,
		std::placeholders::_1)));
	_factory.insert(std::make_pair(Entity::CHECKBOX, std::bind(&IrrLib::addCheckBox, this,
		std::placeholders::_1)));
	_factory.insert(std::make_pair(Entity::LABEL, std::bind(&IrrLib::addStaticText, this,
		std::placeholders::_1)));
	_factory.insert(std::make_pair(Entity::BUTTON, std::bind(&IrrLib::addButton, this,
		std::placeholders::_1)));
	_factory.insert(std::make_pair(Entity::WALL, std::bind(&IrrLib::addCube, this,
		std::placeholders::_1)));
	_factory.insert(std::make_pair(Entity::CRATE, std::bind(&IrrLib::addCubeCrate, this,
		std::placeholders::_1)));
	_factory.insert(std::make_pair(Entity::LISTBOX, std::bind(&IrrLib::addListBox, this,
		std::placeholders::_1)));
	_factory.insert(std::make_pair(Entity::PLAYER, std::bind(&IrrLib::addPlayer, this,
		std::placeholders::_1)));
	_skybox = _smgr->addSkyBoxSceneNode(
		_driver->getTexture("./media/mp_classm/classmplanet_up.tga"),
		_driver->getTexture("./media/mp_classm/classmplanet_dn.tga"),
		_driver->getTexture("./media/mp_classm/classmplanet_rt.tga"),
		_driver->getTexture("./media/mp_classm/classmplanet_lf.tga"),
		_driver->getTexture("./media/mp_classm/classmplanet_ft.tga"),
		_driver->getTexture("./media/mp_classm/classmplanet_bk.tga"));
	_camTarget = irr::core::vector3df(10, 0, 10);
	_camera->setPosition(irr::core::vector3df(0, 0, 0));
}

IrrLib::~IrrLib()
{
}

void IrrLib::createPlane(std::pair<std::size_t, std::size_t> &size)
{
	irr::scene::IMesh* plane = _geomentryCreator->createPlaneMesh(irr::core::dimension2d<irr::f32>(size.first, size.first),
		irr::core::dimension2d<irr::u32>(size.second, size.second));
	_ground = _smgr->addMeshSceneNode(plane);
	_ground->setPosition(irr::core::vector3df(size.first, 0, size.second));
	_ground->setMaterialTexture(0, _driver->getTexture("./media/grass.bmp"));
	_ground->setMaterialFlag(irr::video::EMF_LIGHTING, false);    //This is important
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

void IrrLib::addCubeCrate(std::unique_ptr<IEntity> &entity)
{
	irr::scene::ISceneNode* cube = _smgr->addCubeSceneNode(1);
	cube->setPosition(irr::core::vector3df(entity->getPos().first, 0.5, entity->getPos().second));
	cube->setMaterialTexture(0, _driver->getTexture("./media/crate.jpg"));
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

void IrrLib::addButton(std::unique_ptr<IEntity> &entity)
{
	auto item = static_cast<MenuItem*>(entity.get());
	std::wstring wText;
	std::string str = item->getText();

	for (unsigned int i = 0; i < str.size(); ++i)
		wText += wchar_t(str[i]);
	irr::gui::IGUIButton *button = _guienv->addButton(irr::core::rect<irr::s32>(item->getPos().first,
		item->getPos().second, item->getPos().first + item->getSize().first,
			item->getPos().second + item->getSize().second), 0, item->getId(),
				wText.c_str());
	button->setPressed(item->isSelected());
	button->setDrawBorder(true);
}

void IrrLib::addStaticText(std::unique_ptr<IEntity> &entity)
{
	auto item = static_cast<MenuItem*>(entity.get());
	std::wstring wText;
	std::string str = item->getText();
	irr::gui::IGUIStaticText	*text;

	for (unsigned int i = 0; i < str.size(); ++i)
		wText += wchar_t(str[i]);
	text = _guienv->addStaticText(wText.c_str(), irr::core::rect<irr::s32>(item->getPos().first,
		item->getPos().second, item->getPos().first + item->getSize().first,
			item->getPos().second + item->getSize().second), item->isSelected());
	text->setDrawBackground(true);
	text->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);
	text->setID(item->getId());
	_labels.push_back(text);
}

void IrrLib::addEditBox(std::unique_ptr<IEntity> &entity)
{
	auto item = static_cast<MenuItem*>(entity.get());
	std::wstring wText;
	std::string str = item->getText();

	for (unsigned int i = 0; i < str.size(); ++i)
		wText += wchar_t(str[i]);
	irr::gui::IGUIEditBox *editbox = _guienv->addEditBox(wText.c_str(), irr::core::rect<irr::s32>(item->getPos().first,
		item->getPos().second, item->getPos().first + item->getSize().first,
			item->getPos().second + item->getSize().second));
	editbox->setID(item->getId());
	_inputs.push_back(editbox);
}

void IrrLib::addCheckBox(std::unique_ptr<IEntity> &entity)
{
	auto item = static_cast<MenuItem*>(entity.get());
	std::wstring wText;
	std::string str = item->getText();

	for (unsigned int i = 0; i < str.size(); ++i)
		wText += wchar_t(str[i]);
	irr::gui::IGUICheckBox *checkbox = _guienv->addCheckBox(false, irr::core::rect<irr::s32>(item->getPos().first,
		item->getPos().second, item->getPos().first + item->getSize().first,
			item->getPos().second + item->getSize().second));
	checkbox->setID(item->getId());
	_checkboxes.push_back(checkbox);
}

void IrrLib::addListBox(std::unique_ptr<IEntity> &entity)
{
	auto item = static_cast<MenuItem*>(entity.get());

	_listbox = _guienv->addListBox(irr::core::rect<irr::s32>(item->getPos().first, 
		item->getPos().second,	item->getPos().first + item->getSize().first, 
		item->getPos().second + item->getSize().second));
	_listbox->setItemHeight(20);
//	_listbox->setAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);
	int idx = 0;
	for (auto &i : item->getChoices())
	{
		const wchar_t* kek = i.c_str();
		_listbox->addItem(kek);
		_listbox->setItemOverrideColor(idx, irr::video::SColor(255,255,255,255));
		idx++;
	}
}

bool IrrLib::getRun()
{
	return _device->run();
}

void IrrLib::displayBackground()
{
	_camTarget.rotateXZBy(-0.2, irr::core::vector3df(0, 0, 0));
	_camera->setTarget(_camTarget);
}

void IrrLib::initMenu(std::vector<std::unique_ptr<IEntity>> &menuItems)
{
	_guienv->clear();
	_inputs.clear();
	_labels.clear();
	_checkboxes.clear();
	_eventReceiver.resetIdButtonPressed();
	irr::gui::IGUISkin* skin = _guienv->getSkin();
	irr::gui::IGUIFont* font = _guienv->getFont("./media/myfont.png");
	skin->setFont(_guienv->getBuiltInFont(), irr::gui::EGDF_TOOLTIP);
	if (font)
		skin->setFont(font);
	else
		std::cout << "font not set" << std::endl;
	_skybox->setVisible(true);
	for (auto &it : menuItems) {
		_factory[it->getType()](it);
	}
}

void IrrLib::updateLabel(std::unique_ptr<IEntity> &item)
{
	std::wstring wText;

	for (unsigned int i = 0; i < static_cast<MenuItem*>(item.get())->getText().size(); ++i)
		wText += wchar_t(static_cast<MenuItem*>(item.get())->getText()[i]);
	const wchar_t* newnewlabel = wText.c_str();
	for (auto &it : _labels) {
		if (static_cast<MenuItem*>(item.get())->getId() == (*it).getID()) {
			(*it).setText(newnewlabel);
		}
	}
}

std::wstring IrrLib::getInputText(std::unique_ptr<IEntity> &item)
{
	for (auto it = _inputs.begin(); it != _inputs.end(); it++) {
		if ((*it)->getID() == static_cast<MenuItem*>(item.get())->getId()) {
			return ((*it)->getText());
		}
	}
	return (L"");
}

bool IrrLib::getCheckboxState(std::unique_ptr<IEntity> &item)
{
	for (auto it = _checkboxes.begin(); it != _checkboxes.end(); ++it) {
		if ((*it)->getID() == static_cast<MenuItem*>(item.get())->getId()) {
			return ((*it)->isChecked());
		}
	}
	return (false);
}

std::wstring  IrrLib::getLabelText(std::unique_ptr<IEntity> &item)
{
	for (auto it = _labels.begin(); it != _labels.end(); ++it) {
		if ((*it)->getID() == static_cast<MenuItem*>(item.get())->getId()) {
			return ((*it)->getText());
		}
	}
	return (L"");
}

std::wstring	IrrLib::getListBoxChoice(std::unique_ptr<IEntity> &item)
{
	int toto = _listbox->getSelected();
	return (static_cast<MenuItem*>(item.get())->getChoices()[toto]);
}


int IrrLib::getIdButtonPressed() const
{
	return _eventReceiver.getIdButtonPressed();
}

void IrrLib::drawMenu()
{
	_eventReceiver.resetIdButtonPressed();
	if (_device->isWindowActive()) {
		_driver->beginScene(true, true);
		_smgr->drawAll();
		_guienv->drawAll();
		_driver->endScene();
	}
}

void IrrLib::cleanMenu()
{
	_guienv->clear();
}

void IrrLib::drawGame()
{
	_driver->beginScene(true, true);
	_smgr->drawAll();
	_guienv->drawAll();
	_driver->endScene();
}

void IrrLib::updatePlayer(std::unique_ptr<IEntity> &entity)
{
	for (auto &it : _players) {
		if (it->getID() == static_cast<Player*>(entity.get())->getId()) {
			it->setPosition(irr::core::vector3df(entity->getPos().first, 0.5, entity->getPos().second));
		}
	}
}

void IrrLib::addPlayer(std::unique_ptr<IEntity> &entity)
{
	irr::scene::IAnimatedMesh* mesh = _smgr->getMesh("./media/METAL_SONIC.md2");
	irr::scene::IAnimatedMeshSceneNode* node = _smgr->addAnimatedMeshSceneNode(mesh);
	if (node) {
		node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		node->setMD2Animation(irr::scene::EMAT_STAND);
		node->setMaterialTexture( 0, _driver->getTexture("./media/sydney.bmp") );
		node->setScale(irr::core::vector3df(0.02f, 0.02f, 0.02f));
		node->setPosition(irr::core::vector3df(entity->getPos().first, 0.5, entity->getPos().second));
		_players.push_back(node);
	}
}

void IrrLib::initGame(std::vector<std::unique_ptr<IEntity>> &gameEntities,
	std::pair<std::size_t, std::size_t> size)
{
	_skybox->setVisible(false);
	createPlane(size);
	irr::core::vector3df groundPos = _ground->getPosition();
	_camera->setPosition(irr::core::vector3df(groundPos.X, 20, groundPos.Z));
	_camera->setTarget(groundPos);
	for (auto &it : gameEntities) {
		_factory[it->getType()](it);
	}
}

void IrrLib::affGameEntities(std::vector<std::unique_ptr<IEntity>> &gameEntities)
{
	for (auto &it : gameEntities) {
		_factory[it->getType()](it);
	}
}

void IrrLib::drop()
{
	_device->drop();
}
