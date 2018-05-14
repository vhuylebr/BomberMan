#ifdef _MSC_VER
// We'll also define this to stop MSVC complaining about sprintf().
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "Irrlicht.lib")
#endif
#include <irrlicht.h>
#include <iostream>
#include "driverChoice.h"
#include <vector>

using namespace irr;
using namespace core;
using namespace io;
using namespace gui;

class MyEventReceiver : public IEventReceiver
{
public:
    // This is the one method that we have to implement
    virtual bool OnEvent(const SEvent& event)
    {
	// Remember whether each key is down or up
	if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
	    KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
	}

	return false;
    }

    // This is used to check whether a key is being held down
    virtual bool IsKeyDown(EKEY_CODE keyCode) const
    {
	return KeyIsDown[keyCode];
    }

    MyEventReceiver()
    {
	for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
	    KeyIsDown[i] = false;
    }

private:
    // We use this array to store the current state of each key
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

int main() {
	MyEventReceiver receiver;
	IrrlichtDevice *device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(1600, 1080), 16, false, false, false, &receiver);
	video::IVideoDriver *driver = device->getVideoDriver();
	scene::ISceneManager *smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();
	scene::IAnimatedMesh* mesh = smgr->getMesh("METAL_SONIC.md2");

	const scene::IGeometryCreator *geomentryCreator = smgr->getGeometryCreator();

	if (!mesh) {
		device->drop();
		return 1;
	}
	//sonic
	scene::IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(mesh);
	if (node) {
		node->setMaterialFlag(video::EMF_LIGHTING, false);
		node->setMD2Animation(scene::EMAT_STAND);
		node->setMaterialTexture( 0, driver->getTexture("./media/sydney.bmp") );
		node->setScale(vector3df(0.05f, 0.05f, 0.05f));
	}
	smgr->addCameraSceneNode(0, vector3df(0,30,-40), vector3df(0,5,0));

	scene::IMesh* plane = geomentryCreator->createPlaneMesh(core::dimension2d<f32>(5, 5), core::dimension2d<u32>(5, 5));
	scene::ISceneNode* ground = smgr->addMeshSceneNode(plane);
	ground->setPosition(core::vector3df(0, 0, 0));
	ground->setMaterialTexture(0, driver->getTexture("./media/grass.bmp"));
	ground->setMaterialFlag(video::EMF_LIGHTING, false);    //This is important

	scene::ISceneNode* cube = smgr->addCubeSceneNode(1);
	cube->setPosition(core::vector3df(1, 0.5, 0));
	cube->setMaterialTexture(0, driver->getTexture("./media/wall.bmp"));
	cube->setMaterialFlag(video::EMF_LIGHTING, false);    //This is important
	cube->render();

	std::vector<scene::ISceneNode*> wall;
	for(int i = -10; i < 10; ++i) {
		scene::ISceneNode* cube = smgr->addCubeSceneNode(1);
		cube->setPosition(core::vector3df(i, 0.5, 10));
		cube->setMaterialTexture(0, driver->getTexture("./media/wall.bmp"));
		cube->setMaterialFlag(video::EMF_LIGHTING, false);    //This is important
		cube->render();
		wall.push_back(cube);
	}
	for(int i = -10; i < 11; ++i) {
		scene::ISceneNode* cube = smgr->addCubeSceneNode(1);
		cube->setPosition(core::vector3df(10, 0.5, i));
		cube->setMaterialTexture(0, driver->getTexture("./media/wall.bmp"));
		cube->setMaterialFlag(video::EMF_LIGHTING, false);    //This is important
		cube->render();
		wall.push_back(cube);
	}
	for(int i = -10; i < 10; ++i) {
		scene::ISceneNode* cube = smgr->addCubeSceneNode(1);
		cube->setPosition(core::vector3df(-10, 0.5, i));
		cube->setMaterialTexture(0, driver->getTexture("./media/wall.bmp"));
		cube->setMaterialFlag(video::EMF_LIGHTING, false);    //This is important
		cube->render();
		wall.push_back(cube);
	}
	for(int i = -10; i < 11; ++i) {
		scene::ISceneNode* cube = smgr->addCubeSceneNode(1);
		cube->setPosition(core::vector3df(i, 0.5, -10));
		cube->setMaterialTexture(0, driver->getTexture("./media/wall.bmp"));
		cube->setMaterialFlag(video::EMF_LIGHTING, false);    //This is important
		cube->render();
		wall.push_back(cube);
	}
	scene::ICameraSceneNode* cam = smgr->addCameraSceneNode();
	core::vector3df camPos(0, 20, 0);
	core::vector3df cubePos(9, 0.5, 9);
	cam->setPosition(camPos);    //This is also important
	// smgr->addCameraSceneNode();
	// smgr->addMeshSceneNode(plane);
	while(device->run()){
		driver->beginScene(true, true, video::SColor(0, 0, 0, 0));    //Important for the background to be white
		driver->draw3DLine(core::vector3df(1000, 0, 0), core::vector3df(-1000, 0, 0));
		driver->draw3DLine(core::vector3df(0, 1000, 0), core::vector3df(0, -1000, 0));
		driver->draw3DLine(core::vector3df(0, 0, 1000), core::vector3df(0, 0, -1000));
		if(receiver.IsKeyDown(irr::KEY_KEY_Z))
			cubePos.set(cubePos.X + 0.1, cubePos.Y, cubePos.Z);
		if(receiver.IsKeyDown(irr::KEY_KEY_S))
			cubePos.set(cubePos.X - 0.1, cubePos.Y, cubePos.Z);
		if(receiver.IsKeyDown(irr::KEY_KEY_Q))
			cubePos.set(cubePos.X, cubePos.Y, cubePos.Z + 0.1);
		if(receiver.IsKeyDown(irr::KEY_KEY_D))
			cubePos.set(cubePos.X, cubePos.Y, cubePos.Z - 0.1);

		if(receiver.IsKeyDown(irr::KEY_LEFT))
			camPos.rotateXZBy(-1.0, cubePos);
		if(receiver.IsKeyDown(irr::KEY_RIGHT))
			camPos.rotateXZBy(1.0, cubePos);
		if(receiver.IsKeyDown(irr::KEY_DOWN))
			camPos.set(camPos.X - (cubePos.X - camPos.X) / 100 , camPos.Y - (cubePos.Y - camPos.Y) / 100, camPos.Z - (cubePos.Z - camPos.Z) / 100);
		if(receiver.IsKeyDown(irr::KEY_UP))
			camPos.set(camPos.X + (cubePos.X - camPos.X) / 100 , camPos.Y + (cubePos.Y - camPos.Y) / 100, camPos.Z + (cubePos.Z - camPos.Z) / 100);

		// if(receiver.IsKeyDown(irr::KEY_KEY_F))
		cube->setPosition(cubePos);
		cam->setTarget(core::vector3df(0, 0, 0));
		cam->setPosition(camPos);
		// cam->setTarget(camPos);
		guienv->drawAll();
		smgr->drawAll();
		driver->endScene();
	}
}
