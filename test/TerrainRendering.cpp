#include <irrlicht.h>
#include "driverChoice.h"

using namespace irr;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif


class MyEventReceiver : public IEventReceiver
{
public:

    MyEventReceiver(scene::ISceneNode* terrain, scene::ISceneNode* skybox, scene::ISceneNode* skydome) :
        Terrain(terrain), Skybox(skybox), Skydome(skydome), showBox(true), showDebug(false)
    {
        Skybox->setVisible(showBox);
        Skydome->setVisible(!showBox);
    }

    bool OnEvent(const SEvent& event)
    {
        // check if user presses the key 'W' or 'D'
        if (event.EventType == irr::EET_KEY_INPUT_EVENT && !event.KeyInput.PressedDown)
        {
            switch (event.KeyInput.Key)
            {
            case irr::KEY_KEY_W: // switch wire frame mode
                Terrain->setMaterialFlag(video::EMF_WIREFRAME,
                        !Terrain->getMaterial(0).Wireframe);
                Terrain->setMaterialFlag(video::EMF_POINTCLOUD, false);
                return true;
            case irr::KEY_KEY_P: // switch wire frame mode
                Terrain->setMaterialFlag(video::EMF_POINTCLOUD,
                        !Terrain->getMaterial(0).PointCloud);
                Terrain->setMaterialFlag(video::EMF_WIREFRAME, false);
                return true;
            case irr::KEY_KEY_D: // toggle detail map
                Terrain->setMaterialType(
                    Terrain->getMaterial(0).MaterialType == video::EMT_SOLID ?
                    video::EMT_DETAIL_MAP : video::EMT_SOLID);
                return true;
            case irr::KEY_KEY_S: // toggle skies
                showBox=!showBox;
                Skybox->setVisible(showBox);
                Skydome->setVisible(!showBox);
                return true;
            case irr::KEY_KEY_X: // toggle debug information
                showDebug=!showDebug;
                Terrain->setDebugDataVisible(showDebug?scene::EDS_BBOX_ALL:scene::EDS_OFF);
                return true;
            default:
                break;
            }
        }

        return false;
    }

private:
    scene::ISceneNode* Terrain;
    scene::ISceneNode* Skybox;
    scene::ISceneNode* Skydome;
    bool showBox;
    bool showDebug;
};
int main()
{
    // ask user for driver
    video::E_DRIVER_TYPE driverType=driverChoiceConsole();
    if (driverType==video::EDT_COUNT)
        return 1;

    // create device with full flexibility over creation parameters
    // you can add more parameters if desired, check irr::SIrrlichtCreationParameters
    irr::SIrrlichtCreationParameters params;
    params.DriverType=driverType;
    params.WindowSize=core::dimension2d<u32>(640, 480);
    IrrlichtDevice* device = createDeviceEx(params);

    if (device == 0)
        return 1; // could not create selected driver.
         video::IVideoDriver* driver = device->getVideoDriver();
    scene::ISceneManager* smgr = device->getSceneManager();
    gui::IGUIEnvironment* env = device->getGUIEnvironment();

    driver->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);

    // add irrlicht logo
    env->addImage(driver->getTexture("../../media/irrlichtlogo2.png"),
        core::position2d<s32>(10,10));

    //set other font
    env->getSkin()->setFont(env->getFont("../../media/fontlucida.png"));

    // add some help text
    env->addStaticText(
        L"Press 'W' to change wireframe mode\nPress 'D' to toggle detail map\nPress 'S' to toggle skybox/skydome",
        core::rect<s32>(10,421,250,475), true, true, 0, -1, true);

    // add camera
    scene::ICameraSceneNode* camera =
        smgr->addCameraSceneNodeFPS(0,100.0f,1.2f);

    camera->setPosition(core::vector3df(2700*2,255*2,2600*2));
    camera->setTarget(core::vector3df(2397*2,343*2,2700*2));
    camera->setFarValue(42000.0f);

    // disable mouse cursor
    device->getCursorControl()->setVisible(false);
    // add terrain scene node
    scene::ITerrainSceneNode* terrain = smgr->addTerrainSceneNode(
        "../../media/terrain-heightmap.bmp",
        0,                  // parent node
        -1,                 // node id
        core::vector3df(0.f, 0.f, 0.f),     // position
        core::vector3df(0.f, 0.f, 0.f),     // rotation
        core::vector3df(40.f, 4.4f, 40.f),  // scale
        video::SColor ( 255, 255, 255, 255 ),   // vertexColor
        5,                  // maxLOD
        scene::ETPS_17,             // patchSize
        4                   // smoothFactor
        );

    terrain->setMaterialFlag(video::EMF_LIGHTING, false);

    terrain->setMaterialTexture(0,
            driver->getTexture("../../media/terrain-texture.jpg"));
    terrain->setMaterialTexture(1,
            driver->getTexture("../../media/detailmap3.jpg"));
    
    terrain->setMaterialType(video::EMT_DETAIL_MAP);

    terrain->scaleTexture(1.0f, 20.0f);
    // create triangle selector for the terrain 
    scene::ITriangleSelector* selector
        = smgr->createTerrainTriangleSelector(terrain, 0);
    terrain->setTriangleSelector(selector);

    // create collision response animator and attach it to the camera
    scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
        selector, camera, core::vector3df(60,100,60),
        core::vector3df(0,0,0),
        core::vector3df(0,50,0));
    selector->drop();
    camera->addAnimator(anim);
    anim->drop();
    scene::CDynamicMeshBuffer* buffer = new scene::CDynamicMeshBuffer(video::EVT_2TCOORDS, video::EIT_16BIT);
    terrain->getMeshBufferForLOD(*buffer, 0);
    video::S3DVertex2TCoords* data = (video::S3DVertex2TCoords*)buffer->getVertexBuffer().getData();
    // Work on data or get the IndexBuffer with a similar call.
    buffer->drop(); // When done drop the buffer again.
     // create skybox and skydome
    driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, false);

    scene::ISceneNode* skybox=smgr->addSkyBoxSceneNode(
        driver->getTexture("../../media/irrlicht2_up.jpg"),
        driver->getTexture("../../media/irrlicht2_dn.jpg"),
        driver->getTexture("../../media/irrlicht2_lf.jpg"),
        driver->getTexture("../../media/irrlicht2_rt.jpg"),
        driver->getTexture("../../media/irrlicht2_ft.jpg"),
        driver->getTexture("../../media/irrlicht2_bk.jpg"));
    scene::ISceneNode* skydome=smgr->addSkyDomeSceneNode(driver->getTexture("../../media/skydome.jpg"),16,8,0.95f,2.0f);

    driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, true);

    // create event receiver
    MyEventReceiver receiver(terrain, skybox, skydome);
    device->setEventReceiver(&receiver);
     int lastFPS = -1;

    while(device->run())
    if (device->isWindowActive())
    {
        driver->beginScene(true, true, 0 );

        smgr->drawAll();
        env->drawAll();

        driver->endScene();

        // display frames per second in window title
        int fps = driver->getFPS();
        if (lastFPS != fps)
        {
            core::stringw str = L"Terrain Renderer - Irrlicht Engine [";
            str += driver->getName();
            str += "] FPS:";
            str += fps;
            // Also print terrain height of current camera position
            // We can use camera position because terrain is located at coordinate origin
            str += " Height: ";
            str += terrain->getHeight(camera->getAbsolutePosition().X,
                    camera->getAbsolutePosition().Z);

            device->setWindowCaption(str.c_str());
            lastFPS = fps;
        }
    }

    device->drop();
    
    return 0;
}