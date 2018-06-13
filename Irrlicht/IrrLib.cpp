/*
** EPITECH PROJECT, 2018
** irrlicht
** File description:
** irrlicht
*/

#include "IrrLib.hpp"

IrrLib::IrrLib(Actions &KeyIsDown)
	:_actions(KeyIsDown), _ground(nullptr), _screenSizeX(SCREEN_WIDTH), _screenSizeY(SCREEN_HEIGHT), _splitScreen(false), _lastFps(0), _altitude(10)
{
	_device = createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(SCREEN_WIDTH, SCREEN_HEIGHT),
			       16, true, true, true, &_eventReceiver);
	_device->setWindowCaption(L"Irrlicht Engine - User Interface");
	_device->setResizable(false);
	_driver = _device->getVideoDriver();
	_smgr = _device->getSceneManager();
	_cameras[0] = _smgr->addCameraSceneNode();
	_cameras[1] = _smgr->addCameraSceneNode();
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
	_factory.insert(std::make_pair(Entity::CUBE, std::bind(&IrrLib::addCube, this,
		std::placeholders::_1)));
	_factory.insert(std::make_pair(Entity::LISTBOX, std::bind(&IrrLib::addListBox, this,
		std::placeholders::_1)));
	_factory.insert(std::make_pair(Entity::PLAYER, std::bind(&IrrLib::addPlayer, this,
		std::placeholders::_1)));
	_factory.insert(std::make_pair(Entity::SPHERE, std::bind(&IrrLib::addSphere, this,
		std::placeholders::_1)));
	_factory.insert(std::make_pair(Entity::ITEM, std::bind(&IrrLib::addItem, this,
		std::placeholders::_1)));
	_factoryUpdate.insert(std::make_pair(Entity::PLAYER, std::bind(&IrrLib::updatePlayer, this,
		std::placeholders::_1)));
	_factoryUpdate.insert(std::make_pair(Entity::SPHERE, std::bind(&IrrLib::updateSphere, this,
		std::placeholders::_1)));
	_factoryUpdate.insert(std::make_pair(Entity::CUBE, std::bind(&IrrLib::updateCube, this,
		std::placeholders::_1)));
	_factoryUpdate.insert(std::make_pair(Entity::BUTTON, std::bind(&IrrLib::updateButton, this,
		std::placeholders::_1)));
	_factoryUpdate.insert(std::make_pair(Entity::ITEM, std::bind(&IrrLib::updateItem, this,
		std::placeholders::_1)));
	_factoryUpdate.insert(std::make_pair(Entity::LABEL, std::bind(&IrrLib::updateLabel, this,
		std::placeholders::_1)));
	_factoryDelete.insert(std::make_pair(Entity::CUBE, std::bind(&IrrLib::removeCube, this,
		std::placeholders::_1)));
	_factoryDelete.insert(std::make_pair(Entity::ITEM, std::bind(&IrrLib::removeItem, this,
		std::placeholders::_1)));
	_factoryDelete.insert(std::make_pair(Entity::SPHERE, std::bind(&IrrLib::removeSphere, this,
		std::placeholders::_1)));
	_camTarget = irr::core::vector3df(10, 0, 10);
	_camera->setPosition(irr::core::vector3df(0, 0, 0));
	_gamemusic.load(SOUND::TICTAC, "./media/Sound/bombwait.wav");
	_gamemusic.setVol(SOUND::TICTAC, 0.3);
	_gamemusic.load(SOUND::BOOM, "./media/Sound/explosion.wav");
	_gamemusic.load(SOUND::POWERUP, "./media/Sound/powerup.wav");
	_gamemusic.setVol(SOUND::POWERUP, 0.1);
	_gamemusic.load(SOUND::LOSE, "./media/Sound/lose.wav");
	_gamemusic.load(SOUND::WIN, "./media/Sound/lose.wav");
	_gamemusic.load(SOUND::DMG, "./media/Sound/damage.ogg");
	
	irr::core::array<irr::SJoystickInfo> joystickInfo;
	if (_device->activateJoysticks(joystickInfo)) {
		std::cout << "Joystick support is enabled" << std::endl;
	} else {
		std::cout << "Joystick support is not enabled." << std::endl;
	}
	_anim = _smgr->createRotationAnimator(irr::core::vector3df(1,0,0));
	_noAnim = _smgr->createRotationAnimator(irr::core::vector3df(0,0,0));
}

IrrLib::~IrrLib()
{
}

void	IrrLib::createPlane(pairUC &size)
{
	irr::scene::IMesh* plane = _geomentryCreator->createPlaneMesh(irr::core::dimension2d<irr::f32>(15, 15),
		irr::core::dimension2d<irr::u32>(15, 15));
	_ground = _smgr->addMeshSceneNode(plane);
	_ground->setPosition(irr::core::vector3df(0, 0, 0));
	_ground->setMaterialTexture(0, _driver->getTexture("./media/sand.png"));
	_ground->setMaterialFlag(irr::video::EMF_LIGHTING, false);    //This is important
}

void	IrrLib::addSphere(std::unique_ptr<IEntity> &entity)
{
	for (auto &it : _spheres) {
		if (it->getID() == -1) {
			it->setID(entity->getId());
			it->setPosition(irr::core::vector3df(entity->getPos().first, 0, entity->getPos().second));
			it->setMaterialType(irr::video::EMT_SOLID);
			it->setMaterialTexture(0, _driver->getTexture(static_cast<ASphere*>(entity.get())->getTexture().c_str())); //"./media/bomb.png"
			it->setVisible(true);
			it->setScale({static_cast<ASphere*>(entity.get())->getScale(),static_cast<ASphere*>(entity.get())->getScale(),static_cast<ASphere*>(entity.get())->getScale()});
			it->removeAnimators();
			if (static_cast<ASphere*>(entity.get())->getSubType() == SphereSubType::SUBBOMB) {
				_gamemusic.play(SOUND::TICTAC);
				it->setName("Bomb");
			} else {
				it->addAnimator(_anim);
				it->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
				it->setName("Shield");
			}
			it->render();
			return;
		}
	}
	irr::scene::IMesh* sphere = _geomentryCreator->createSphereMesh();
	irr::scene::ISceneNode* ball = _smgr->addMeshSceneNode(sphere);
	ball->setPosition(irr::core::vector3df(entity->getPos().first, 0, entity->getPos().second));
	ball->setMaterialTexture(0, _driver->getTexture(static_cast<ASphere*>(entity.get())->getTexture().c_str()));
	ball->setMaterialFlag(irr::video::EMF_LIGHTING, false);    //This is important
	ball->setVisible(static_cast<ASphere*>(entity.get())->isAlive()); // No, You're important...
	ball->setID(static_cast<ASphere*>(entity.get())->getId());
	ball->setScale({static_cast<ASphere*>(entity.get())->getScale(),static_cast<ASphere*>(entity.get())->getScale(),static_cast<ASphere*>(entity.get())->getScale()});
	ball->setMaterialType(irr::video::EMT_SOLID);
	ball->removeAnimators();
	if (static_cast<ASphere*>(entity.get())->getSubType() == SphereSubType::SUBBOMB) {
		_gamemusic.play(SOUND::TICTAC);
		ball->setName("Bomb");
	} else {
		ball->addAnimator(_anim);
		ball->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
		ball->setName("Shield");
	}
	_spheres.push_back(ball);
}

void	IrrLib::updateSphere(std::unique_ptr<IEntity> &entity)
{
	for (auto &it : _spheres) {
		if (it->getID() == entity->getId()) {
			it->setPosition(irr::core::vector3df(entity->getPos().first, 0.5, entity->getPos().second));
			it->setVisible(static_cast<ASphere*>(entity.get())->isAlive());
			it->setMaterialTexture(0, _driver->getTexture(static_cast<ASphere*>(entity.get())->getTexture().c_str()));
			it->setScale({static_cast<ASphere*>(entity.get())->getScale(),static_cast<ASphere*>(entity.get())->getScale(),static_cast<ASphere*>(entity.get())->getScale()});
			return ;
		}
	}
	addSphere(entity);
}

void	IrrLib::removeSphere(int id)
{
	int i = 0;

	for (auto &it : _spheres) {
		if (id == it->getID()) {
			it->setMaterialType(irr::video::EMT_SOLID);
			if (!std::string("Bomb").compare(it->getName()))
			    _gamemusic.play(SOUND::BOOM);
			it->setID(-1);
			it->addAnimator(_noAnim);
			it->setVisible(false);
			it->removeAll();
			break;
		}
		++i;
	}
}

void	IrrLib::addCube(std::unique_ptr<IEntity> &entity)
{
	for (auto &it : _cubes) {
		if (it->getID() == -1) {
			it->setPosition(irr::core::vector3df(entity->getPos().first, 0.5, entity->getPos().second));
			it->setMaterialTexture(0, _driver->getTexture(static_cast<ACube*>(entity.get())->getTexture().c_str()));
			it->setMaterialFlag(irr::video::EMF_LIGHTING, false);    //This is important
			it->setID(static_cast<ACube*>(entity.get())->getId());
			it->setVisible(true);
			it->render();
			return;
		}
	}
	irr::scene::ISceneNode* cube = _smgr->addCubeSceneNode(1);
	cube->setPosition(irr::core::vector3df(entity->getPos().first, 0.5, entity->getPos().second));
	cube->setMaterialTexture(0, _driver->getTexture(static_cast<ACube*>(entity.get())->getTexture().c_str()));
	cube->setMaterialFlag(irr::video::EMF_LIGHTING, false);    //This is important
	cube->setID(static_cast<ACube*>(entity.get())->getId());
	cube->render();
	_cubes.push_back(cube);
}

void	IrrLib::updateCube(std::unique_ptr<IEntity> &entity)
{
	for (auto &it : _cubes) {
		if (it->getID() == static_cast<ACube*>(entity.get())->getId()) {
			it->setPosition(irr::core::vector3df(entity->getPos().first, 0.5, entity->getPos().second));
			it->setVisible(static_cast<ACube*>(entity.get())->isAlive());
			return ;
		}
	}
	addCube(entity);
}

void IrrLib::removeCube(int id)
{
	if (id < 0)
		return;
	for (auto &it : _cubes) {
		if (id == it->getID()) {
			it->setID(-1);
			it->setVisible(false);
			it->removeAll();
			break;
		}
	}
}

Actions	IrrLib::getActions()
{
	const irr::SEvent::SJoystickEvent &joystickData = _eventReceiver.GetJoystickState();
	irr::f32 moveHorizontal = 0;
	irr::f32 moveVertical = 0;
	moveHorizontal = (irr::f32)joystickData.Axis[irr::SEvent::SJoystickEvent::AXIS_X] / 32767.f;
	moveVertical = (irr::f32)joystickData.Axis[irr::SEvent::SJoystickEvent::AXIS_Y] / -32767.f;

	_actions.escape = false;
	_actions.space = false;
	_actions.right = false;
	_actions.left = false;
	_actions.up = false;
	_actions.down = false;
	_actions.enter = false;
	_actions.Z = false;
	_actions.Q = false;
	_actions.S = false;
	_actions.D = false;
	_actions.W = false;
	_actions.buttonPressed = getIdButtonPressed();
	if (_eventReceiver.IsKeyDown(irr::KEY_LEFT) || moveHorizontal < -0.8f)
		_actions.left = true;
	if (_eventReceiver.IsKeyDown(irr::KEY_RIGHT) || moveHorizontal > 0.8f)
		_actions.right = true;
	if (_eventReceiver.IsKeyDown(irr::KEY_UP) || moveVertical > 0.8f)
		_actions.up = true;
	if (_eventReceiver.IsKeyDown(irr::KEY_DOWN) || moveVertical < -0.8f)
		_actions.down = true;
	if (_eventReceiver.IsKeyDown(irr::KEY_ESCAPE) || (irr::u32)joystickData.IsButtonPressed(7))
		_actions.escape = true;
	if (_eventReceiver.IsKeyDown(irr::KEY_SPACE) || (irr::u32)joystickData.IsButtonPressed(0))
		_actions.space = true;
	if (_eventReceiver.IsKeyDown(irr::KEY_RETURN))
		_actions.enter = true;
	if (_eventReceiver.IsKeyDown(irr::KEY_KEY_Q))
		_actions.Q = true;
	if (_eventReceiver.IsKeyDown(irr::KEY_KEY_S))
		_actions.S = true;
	if (_eventReceiver.IsKeyDown(irr::KEY_KEY_D))
		_actions.D = true;
	if (_eventReceiver.IsKeyDown(irr::KEY_KEY_Z))
		_actions.Z = true;
	if (_eventReceiver.IsKeyDown(irr::KEY_KEY_W))
		_actions.W = true;
	return (_actions);
}

void IrrLib::addButton(std::unique_ptr<IEntity> &entity)
{
	MenuItem *item = static_cast<MenuItem*>(entity.get());
	std::wstring wText;
	std::string str = item->getText();

	for (unsigned int i = 0; i < str.size(); ++i)
		wText += wchar_t(str[i]);
	irr::gui::IGUIButton *button = _guienv->addButton(irr::core::rect<irr::s32>(item->getPos().first,
		item->getPos().second, item->getPos().first + item->getSize().first,
			item->getPos().second + item->getSize().second), 0, item->getId(),
				wText.c_str());
	if (item->isSetTexture() == true)
		button->setImage(_driver->getTexture(item->getTexture().c_str()));
	_buttons.push_back(button);
}


void IrrLib::updateButton(std::unique_ptr<IEntity> &entity)
{
	for (auto &it : _buttons) {
		if (static_cast<MenuItem*>(entity.get())->getId() == it->getID()) {
			return;
		}
	}
	addButton(entity);
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
	checkbox->setChecked(true);
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
	int idx = 0;
	for (auto &i : item->getChoices())
	{
		const wchar_t* tmp = i.c_str();
		_listbox->addItem(tmp);
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
	_buttons.clear();
	_eventReceiver.resetIdButtonPressed();
	_skybox = _smgr->addSkyBoxSceneNode(
	_driver->getTexture("./media/arrakisday/arrakisday_up.tga"),
	_driver->getTexture("./media/arrakisday/arrakisday_dn.tga"),
	_driver->getTexture("./media/arrakisday/arrakisday_rt.tga"),
	_driver->getTexture("./media/arrakisday/arrakisday_lf.tga"),
	_driver->getTexture("./media/arrakisday/arrakisday_ft.tga"),
	_driver->getTexture("./media/arrakisday/arrakisday_bk.tga"));
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

void IrrLib::updateLabel(std::unique_ptr<IEntity> &entity)
{
	std::wstring wText;
	for (auto &it : _labels) {
		if (static_cast<MenuItem*>(entity.get())->getId() == it->getID()) {
			for (unsigned int i = 0; i < static_cast<MenuItem*>(entity.get())->getText().size(); ++i)
					wText += wchar_t(static_cast<MenuItem*>(entity.get())->getText()[i]);
				const wchar_t* newnewlabel = wText.c_str();
				it->setText(newnewlabel);
			return;
		}
	}
	addStaticText(entity);
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
	if (toto == -1)
		return (L"");
	else
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
	for (auto &it : _inputs)
		it->remove();
	for (auto &it : _checkboxes)
		it->remove();
	for (auto &it : _labels)
		it->remove();
	for (auto &it : _buttons)
		it->remove();
	_inputs.clear();
	_checkboxes.clear();
	_labels.clear();
	_buttons.clear();
	_skybox->remove();
	_guienv->clear();
}

void IrrLib::drawGame()
{
	_eventReceiver.resetIdButtonPressed();
	_driver->beginScene(true, true);
	if (_eventReceiver.IsKeyDown(irr::KEY_KEY_P))
		_splitScreen = !_splitScreen;
	if (_splitScreen) {
		irr::core::vector3df camPos = _players[0]->getPosition();
		_cameras[0]->setPosition(irr::core::vector3df(camPos.X, 10, camPos.Z - 0.1));
		_cameras[0]->setTarget(_players[0]->getPosition());
		camPos = _players[1]->getPosition();
		_cameras[1]->setPosition(irr::core::vector3df(camPos.X, 10, camPos.Z - 0.1));
		_cameras[1]->setTarget(_players[1]->getPosition());
		_smgr->setActiveCamera(_cameras[0]);
		_driver->setViewPort(irr::core::rect<irr::s32>(0,0,_screenSizeX / 2, _screenSizeY / 2));
		_smgr->drawAll();
		_smgr->setActiveCamera(_cameras[1]);
		_driver->setViewPort(irr::core::rect<irr::s32>(_screenSizeX / 2, _screenSizeY / 2, _screenSizeX, _screenSizeY));
		_smgr->drawAll();
	}
	_driver->setViewPort(irr::core::rect<irr::s32>(0, 0, _screenSizeX, _screenSizeY));
	if (_splitScreen == false) {
		if (_eventReceiver.IsKeyDown(irr::KEY_KEY_U))
			_altitude++;
		if (_eventReceiver.IsKeyDown(irr::KEY_KEY_J))
			_altitude--;
		irr::core::vector3df camPos = _players[0]->getPosition();
		_camera->setPosition(irr::core::vector3df(camPos.X, _altitude, camPos.Z - 0.1));
		_camera->setTarget(camPos);
		_smgr->setActiveCamera(_camera);
		_smgr->drawAll();
	}
	_guienv->drawAll();
	_driver->endScene();
	
	int fps = _driver->getFPS();
	if (_lastFps != fps) {
			irr::core::stringw tmp(L"BomberMan [");
			tmp += _driver->getName();
			tmp += L"] fps: ";
			tmp += fps;
			_device->setWindowCaption(tmp.c_str());
			_lastFps = fps;
	}
}

void IrrLib::updatePlayer(std::unique_ptr<IEntity> &entity)
{
	for (auto &it : _players) {
		if (it->getID() == static_cast<Player*>(entity.get())->getId()) {
			it->setRotation(irr::core::vector3df(0, static_cast<Player*>(entity.get())->getRotation(), 0));
			it->setPosition(irr::core::vector3df(entity->getPos().first, 0.5, entity->getPos().second));
			it->setVisible(static_cast<Player*>(entity.get())->isAlive());
			if (static_cast<Player*>(entity.get())->wasDamaged() == true)
				_gamemusic.play(SOUND::DMG);
			if (static_cast<Player*>(entity.get())->hasPickedUp() == true)
				_gamemusic.play(SOUND::POWERUP);
		}
	}
}

void IrrLib::addPlayer(std::unique_ptr<IEntity> &entity)
{
	irr::scene::IAnimatedMesh* mesh = _smgr->getMesh("./media/EGGM.md2");
	irr::scene::IAnimatedMeshSceneNode* node = _smgr->addAnimatedMeshSceneNode(mesh);
	if (node) {
		node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		node->setMD2Animation(irr::scene::EMAT_STAND);
		node->setMaterialTexture( 0, _driver->getTexture("./media/EGGM.PNG"));
		node->setScale(irr::core::vector3df(0.01f, 0.01f, 0.01f));
		node->setPosition(irr::core::vector3df(entity->getPos().first, 0.5, entity->getPos().second));
		node->setID(static_cast<Player*>(entity.get())->getId());
		_players.push_back(node);
	}
}

void IrrLib::updateItem(std::unique_ptr<IEntity> &entity)
{
	for (auto &it : _items) {
		if (it->getID() == static_cast<Item*>(entity.get())->getId()) {
			it->setPosition(irr::core::vector3df(entity->getPos().first, 0.5, entity->getPos().second));
			it->setVisible(static_cast<Item*>(entity.get())->isAlive());
			return;
		}
	}
	addItem(entity);
}

void IrrLib::addItem(std::unique_ptr<IEntity> &entity)
{
	irr::scene::IAnimatedMesh* mesh = _smgr->getMesh(static_cast<Item*>(entity.get())->getModel().c_str());
	for (auto &it : _items) {
		if (it->getID() == -1) {
			it->setMesh(mesh);
			it->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			it->setMD2Animation(irr::scene::EMAT_STAND);
			it->setVisible(true);
			it->setMaterialTexture( 0, _driver->getTexture(static_cast<Item*>(entity.get())->getTexture().c_str()));
			it->setScale(irr::core::vector3df(static_cast<Item*>(entity.get())->getScale(), static_cast<Item*>(entity.get())->getScale(), static_cast<Item*>(entity.get())->getScale()));
			it->setPosition(irr::core::vector3df(entity->getPos().first, 0.5, entity->getPos().second));
			it->setID(static_cast<Item*>(entity.get())->getId());
			return;
		}
	}
	irr::scene::IAnimatedMeshSceneNode* node = _smgr->addAnimatedMeshSceneNode(mesh);
	if (node) {
		node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		node->setMD2Animation(irr::scene::EMAT_STAND);
		node->setMaterialTexture(0, _driver->getTexture(static_cast<Item*>(entity.get())->getTexture().c_str()));
		node->setScale(irr::core::vector3df(static_cast<Item*>(entity.get())->getScale(), static_cast<Item*>(entity.get())->getScale(), static_cast<Item*>(entity.get())->getScale()));
		node->setPosition(irr::core::vector3df(entity->getPos().first, 0.5, entity->getPos().second));
		node->setID(static_cast<Item*>(entity.get())->getId());
		_items.push_back(node);
	}
}

void IrrLib::removeItem(int id)
{
	if (id < 0)
		return;
	for (auto &it : _items) {
		if (id == it->getID()) {
			it->setID(-1);
			it->setVisible(false);
			it->removeAll();
			break;
		}
	}
}

void IrrLib::initGame(pairUC size, std::vector<std::unique_ptr<IEntity> >	&mobileEntities)
{
	drop();
	createPlane(size);
	for (auto &it3: mobileEntities) {
		_factory[it3->getType()](it3);
	}
	if (!_splitScreen) {
		_camera->setPosition(irr::core::vector3df(size.first / 2, 20, size.second / 2 - 1));
		_camera->setTarget(irr::core::vector3df(size.first / 2, 0, size.second / 2));
	}
}

void IrrLib::affGameEntities(std::vector<std::unique_ptr<IEntity>> &gameEntities)
{
	for (auto &it : gameEntities) {
		_factoryUpdate[it->getType()](it);
	}
}

void IrrLib::drop()
{
	for (auto &it : _spheres) {
		it->remove();
	}
	for (auto &it : _players) {
		it->remove();
	}
	for (auto &it : _cubes) {
		it->remove();
	}
	for (auto &it : _items) {
		it->remove();
	}
	if (_ground)
		_ground->remove();
	for (auto &it : _buttons) {
		it->remove();
	}
	for (auto &it : _labels) {
		it->remove();
	}
	for (auto &it : _checkboxes) {
		it->remove();
	}
	for (auto &it : _inputs) {
		it->remove();
	}
	_skybox = NULL;//->remove() doesn't work because already deleted after menu clean;
	_buttons.clear();
	_spheres.clear();
	_players.clear();
	_cubes.clear();
	_items.clear();
	_labels.clear();
}

void IrrLib::setVisible(bool state, int id)
{
	for (auto it = _buttons.begin(); it != _buttons.end(); it++) {
		if ((*it)->getID() == id)
			(*it)->setVisible(state);
	}
}

void IrrLib::removeEntities(std::vector<std::pair<int, Entity> > &vectorToRemove)
{
	for (auto &it : vectorToRemove) {
		_factoryDelete[it.second](it.first);
	}
}

void IrrLib::newMenuItems(std::vector<std::unique_ptr<IEntity>> &menuItems)
{
	for (auto &it : menuItems) {
		_factory[it->getType()](it);
	}
}

void IrrLib::setSplitScreen(bool split)
{
	_splitScreen = split;
}
