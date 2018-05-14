#include <irrlicht.h>
#include <iostream>

using namespace irr;

int main() {
	// ask user for driver

	video::E_DRIVER_TYPE driverType;

    printf("Please select the driver you want for this example:\n"\
	" (a) OpenGL 1.5\n (b) Direct3D 9.0c\n (c) Direct3D 8.1\n"\
	" (d) Burning's Software Renderer\n (e) Software Renderer\n"\
	" (f) NullDevice\n (otherKey) exit\n\n");

	char i;
	std::cin >> i;

	switch(i)
	{
		case 'a': driverType = video::EDT_OPENGL;   break;
		case 'b': driverType = video::EDT_DIRECT3D9;break;
		case 'c': driverType = video::EDT_DIRECT3D8;break;
		case 'd': driverType = video::EDT_BURNINGSVIDEO;break;
		case 'e': driverType = video::EDT_SOFTWARE; break;
		case 'f': driverType = video::EDT_NULL;     break;
		default: return 1;
	}

	// create device and exit if creation failed

	IrrlichtDevice *device =
		createDevice(driverType, core::dimension2d<u32>(640, 480));

	if (device == 0)
		return 1; // could not create selected driver.
	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();
	device->getFileSystem()->addFileArchive("../../media/map-20kdm2.pk3");
	scene::IAnimatedMesh* mesh = smgr->getMesh("20kdm2.bsp");
	scene::ISceneNode* node = 0;

	if (mesh)
		node = smgr->addOctreeSceneNode(mesh->getMesh(0), 0, -1, 1024);
	//      node = smgr->addMeshSceneNode(mesh->getMesh(0));
	if (node)
		node->setPosition(core::vector3df(-1300,-144,-1249));
	device->getCursorControl()->setVisible(false);
	int lastFPS = -1;

    while(device->run())
    {
	if (device->isWindowActive())
	{
	    driver->beginScene(true, true, video::SColor(255,200,200,200));
	    smgr->drawAll();
	    driver->endScene();

	    int fps = driver->getFPS();

	    if (lastFPS != fps)
	    {
		core::stringw str = L"Irrlicht Engine - Quake 3 Map example [";
		str += driver->getName();
		str += "] FPS:";
		str += fps;

		device->setWindowCaption(str.c_str());
		lastFPS = fps;
	    }
	}
	else
	    device->yield();
    }
    device->drop();
    return 0;
}