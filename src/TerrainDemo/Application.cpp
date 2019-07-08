
#include <memory>
#include <string>

#include <TerrainDemo/core/Log.h>
#include <TerrainDemo/core/Utils.h>
#include <TerrainDemo/core/SDLRenderer.h>
#include <TerrainDemo/core/SDLControls.h>

#include <TerrainDemo/Application.h>
#include <TerrainDemo/TDScene.h>
#include <TerrainDemo/TerrainDemoVT.h>

using namespace std;
using namespace TerrainDemo;
using namespace TerrainDemo::core;
using namespace sdl2cpp;

Application::Application() {}

Application::~Application() {}

int Application::init()
{
    GPTR_LOG_INFO("Application initiating ...");

    // init terrain demo scene
    auto scene = make_shared<TDScene>();

    auto controls = make_shared<SDLControls>();
    scene->getCamera()->setControls(controls);

    // init window and visualization
    auto window = make_shared<Window>();
    auto mainLoop = make_shared<MainLoop>();

    _renderer = make_shared<SDLRenderer>(
        window,
        mainLoop,
        make_shared<TerrainDemoVT>()
    );

    _renderer->init();
    _renderer->setScene(scene);
    _renderer->setControls(controls);

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
