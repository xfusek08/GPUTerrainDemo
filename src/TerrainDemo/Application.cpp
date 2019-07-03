
#include <memory>
#include <string>

#include <TerrainDemo/Log.h>
#include <TerrainDemo/utils.h>
#include <TerrainDemo/Application.h>
#include <TerrainDemo/SDLRenderer.h>

using namespace std;
using namespace TerrainDemo;
using namespace sdl2cpp;

Application::Application() {}

Application::~Application() {}

int Application::init()
{
    GPTR_LOG_INFO("Application initiating ...");

    auto window = make_shared<Window>();
    auto mainLoop = make_shared<MainLoop>();
    this->_renderer = make_shared<SDLRenderer>(window, mainLoop);

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
