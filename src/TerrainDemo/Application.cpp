
#include <memory>
#include <string>

#include <TerrainDemo/core/Log.h>
#include <TerrainDemo/core/Utils.h>
#include <TerrainDemo/core/Camera.h>

#include <TerrainDemo/tdsdl/SDLRenderer.h>
#include <TerrainDemo/tdsdl/SDLOrbitCameraController.h>

#include <TerrainDemo/Application.h>
#include <TerrainDemo/TerrainScene.h>
#include <TerrainDemo/TerrainVT.h>

using namespace std;
using namespace TerrainDemo;
using namespace TerrainDemo::tdsdl;
using namespace TerrainDemo::core;
using namespace sdl2cpp;

Application::Application() {}

Application::~Application() {}

int Application::init()
{
    GPTR_LOG_INFO("Application initiating ...");

    // init SDL window
    auto window = make_shared<Window>();
    auto mainLoop = make_shared<MainLoop>();

    // init terrain demo scene
    auto scene            = make_shared<TerrainScene>();
    auto camera           = make_shared<Camera>(window->getWidth(), window->getHeight());
    auto cameraController = make_shared<SDLOrbitCameraController>(camera);
    auto vt               = make_shared<TerrainVT>();

    vt->setCamera(camera);
    vt->setScene(scene);

    _renderer = make_shared<SDLRenderer>(
        window,
        mainLoop,
        vt
    );
    _renderer->init();
    _renderer->addEventReceiver(cameraController);

    GPTR_LOG_INFO("Application initialized.");
    return true;
}

int Application::run()
{
    GPTR_LOG_INFO("Application running ...");
    this->_renderer->run();
    GPTR_LOG_INFO("Application end.");
    return 0;
}
