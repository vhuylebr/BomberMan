#ifdef _MSC_VER
// We'll also define this to stop MSVC complaining about sprintf().
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "Irrlicht.lib")
#endif
#include <irrlicht.h>
#include <iostream>
#include "driverChoice.h"



using namespace irr;
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
	IrrlichtDevice *device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(640, 480), 16, false, false, false, &receiver);
	video::IVideoDriver *driver = device->getVideoDriver();
	scene::ISceneManager *sceneManager = device->getSceneManager();
	const scene::IGeometryCreator *geomentryCreator = sceneManager->getGeometryCreator();

	scene::IMesh* plane =
		geomentryCreator->createPlaneMesh(core::dimension2d<f32>(5, 5), core::dimension2d<u32>(5, 5));
	scene::ISceneNode* ground = sceneManager->addMeshSceneNode(plane);
	ground->setPosition(core::vector3df(0, 0, 0));
	ground->setMaterialTexture(0, driver->getTexture("./media/grass.bmp"));
	ground->setMaterialFlag(video::EMF_LIGHTING, false);    //This is important
	
	scene::ISceneNode* cube = sceneManager->addCubeSceneNode(1);
	cube->setPosition(core::vector3df(10, 0.5, 0));
	cube->setMaterialTexture(0, driver->getTexture("./media/wall.bmp"));
	cube->setMaterialFlag(video::EMF_LIGHTING, false);    //This is important
	cube->render();


	scene::ICameraSceneNode* cam = sceneManager->addCameraSceneNode();
	core::vector3df camPos(0, 10, 0);
	cam->setPosition(camPos);    //This is also important
	cam->setTarget(core::vector3df(0, 1, 0));
	// sceneManager->addCameraSceneNodeFPS();
	sceneManager->addMeshSceneNode(plane);
	while(device->run()){
		driver->beginScene(true, true, video::SColor(255, 255, 255, 255));    //Important for the background to be white
		driver->draw3DLine(core::vector3df(1000, 0, 0), core::vector3df(-1000, 0, 0));
		driver->draw3DLine(core::vector3df(0, 1000, 0), core::vector3df(0, -1000, 0));
		driver->draw3DLine(core::vector3df(0, 0, 1000), core::vector3df(0, 0, -1000));
		if(receiver.IsKeyDown(irr::KEY_LEFT))
			camPos.rotateXZBy(-1.0, core::vector3df(0, 1, 0));
		if(receiver.IsKeyDown(irr::KEY_RIGHT))
			camPos.rotateXZBy(1.0, core::vector3df(0, 1, 0));
		if(receiver.IsKeyDown(irr::KEY_DOWN))
			camPos.set(camPos.X - (0 - camPos.X) / 100, camPos.Y - (1 - camPos.Y) / 100, camPos.Z - (0 - camPos.Z) / 100);
		if(receiver.IsKeyDown(irr::KEY_UP))
			camPos.set(camPos.X + (0 - camPos.X) / 100, camPos.Y + (1 - camPos.Y) / 100, camPos.Z + (0 - camPos.Z) / 100);
		cam->setPosition(camPos);
		sceneManager->drawAll();
		driver->endScene();
	}
}