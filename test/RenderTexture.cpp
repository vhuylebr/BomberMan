#include <irrlicht.h>
#include "driverChoice.h"

using namespace irr;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

int main()
{
    // ask user for driver
    video::E_DRIVER_TYPE driverType=driverChoiceConsole();
    if (driverType==video::EDT_COUNT)
        return 1;

    // create device and exit if creation failed

    IrrlichtDevice *device =
        createDevice(driverType, core::dimension2d<u32>(640, 480),
        16, false, false);

    if (device == 0)
        return 1; // could not create selected driver.

    video::IVideoDriver* driver = device->getVideoDriver();
    scene::ISceneManager* smgr = device->getSceneManager();
    gui::IGUIEnvironment* env = device->getGUIEnvironment();
    // load and display animated fairy mesh

    scene::IAnimatedMeshSceneNode* fairy = smgr->addAnimatedMeshSceneNode(
        smgr->getMesh("../../media/faerie.md2"));

    if (fairy)
    {
        fairy->setMaterialTexture(0,
                driver->getTexture("../../media/faerie2.bmp")); // set diffuse texture
        fairy->setMaterialFlag(video::EMF_LIGHTING, true); // enable dynamic lighting
        fairy->getMaterial(0).Shininess = 20.0f; // set size of specular highlights
        fairy->setPosition(core::vector3df(-10,0,-100));
        fairy->setMD2Animation ( scene::EMAT_STAND );
    }
  // add white light
    smgr->addLightSceneNode(0, core::vector3df(-15,5,-105),
            video::SColorf(1.0f, 1.0f, 1.0f));

    // set ambient light
    smgr->setAmbientLight(video::SColor(0,60,60,60));
      // create test cube
    scene::ISceneNode* test = smgr->addCubeSceneNode(60);

    // let the cube rotate and set some light settings
    scene::ISceneNodeAnimator* anim = smgr->createRotationAnimator(
        core::vector3df(0.3f, 0.3f,0));

    test->setPosition(core::vector3df(-100,0,-100));
    test->setMaterialFlag(video::EMF_LIGHTING, false); // disable dynamic lighting
    test->addAnimator(anim);
    anim->drop();

    // set window caption
    device->setWindowCaption(L"Irrlicht Engine - Render to Texture and Specular Highlights example");
     // create render target
    video::ITexture* rt = 0;
    scene::ICameraSceneNode* fixedCam = 0;
    

    if (driver->queryFeature(video::EVDF_RENDER_TO_TARGET))
    {
        rt = driver->addRenderTargetTexture(core::dimension2d<u32>(256,256), "RTT1");
        test->setMaterialTexture(0, rt); // set material of cube to render target

        // add fixed camera
        fixedCam = smgr->addCameraSceneNode(0, core::vector3df(10,10,-80),
            core::vector3df(-10,10,-100));
    }
    else
    {
        // create problem text
        gui::IGUISkin* skin = env->getSkin();
        gui::IGUIFont* font = env->getFont("../../media/fonthaettenschweiler.bmp");
        if (font)
            skin->setFont(font);

        gui::IGUIStaticText* text = env->addStaticText(
            L"Your hardware or this renderer is not able to use the "\
            L"render to texture feature. RTT Disabled.",
            core::rect<s32>(150,20,470,60));

        text->setOverrideColor(video::SColor(100,255,255,255));
    }
    
    // add fps camera
    scene::ICameraSceneNode* fpsCamera = smgr->addCameraSceneNodeFPS();
    fpsCamera->setPosition(core::vector3df(-50,50,-150));

    // disable mouse cursor
    device->getCursorControl()->setVisible(false);
    int lastFPS = -1;

    while(device->run())
    if (device->isWindowActive())
    {
        driver->beginScene(true, true, 0);

        if (rt)
        {
            // draw scene into render target
            
            // set render target texture
            driver->setRenderTarget(rt, true, true, video::SColor(0,0,0,255));

            // make cube invisible and set fixed camera as active camera
            test->setVisible(false);
            smgr->setActiveCamera(fixedCam);

            // draw whole scene into render buffer
            smgr->drawAll();

            // set back old render target
            // The buffer might have been distorted, so clear it
            driver->setRenderTarget(0, true, true, 0);

            // make the cube visible and set the user controlled camera as active one
            test->setVisible(true);
            smgr->setActiveCamera(fpsCamera);
        }
        
        // draw scene normally
        smgr->drawAll();
        env->drawAll();

        driver->endScene();

        // display frames per second in window title
        int fps = driver->getFPS();
        if (lastFPS != fps)
        {
            core::stringw str = L"Irrlicht Engine - Render to Texture and Specular Highlights example";
            str += " FPS:";
            str += fps;

            device->setWindowCaption(str.c_str());
            lastFPS = fps;
        }
    }

    device->drop(); // drop device
    return 0;
}
