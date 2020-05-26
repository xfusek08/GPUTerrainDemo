
#include <memory>

#include <GeoPlanetDemo/core/Log.h>
#include <GeoPlanetDemo/core/Utils.h>
#include <GeoPlanetDemo/core/Camera.h>
#include <GeoPlanetDemo/core/SceneRenderer.h>

#include <GeoPlanetDemo/sdl/SDLGlMainLoop.h>
#include <GeoPlanetDemo/sdl/SDLOrbitCameraController.h>

#include <GeoPlanetDemo/scene/Scene.h>
#include <GeoPlanetDemo/scene/entities/AxisEntity.h>
#include <GeoPlanetDemo/scene/entities/PlanetEntity.h>

#include <GeoPlanetDemo/vt/VTFactory.h>
#include <GeoPlanetDemo/vt/ColorLinesVT.h>
#include <GeoPlanetDemo/vt/planet/PlanetElevationVT.h>

#include <GeoPlanetDemo/Application.h>
#include <GeoPlanetDemo/ApplicationEventReceiver.h>
#include <GeoPlanetDemo/ApplicationGui.h>

using namespace std;
using namespace gpd;
using namespace gpd::sdl;
using namespace gpd::core;
using namespace gpd::scene;
using namespace gpd::scene::entities;
using namespace sdl2cpp;

int Application::init()
{
    GPD_LOG_DEBUG("Application initiating ...");

    // init main components
    mainLoop = make_shared<SDLGlMainLoop>(PROJECT_NAME, Application::DEFAULT_WINDOW_WIDTH, Application::DEFAULT_WINDOW_HEIGHT);
    scene    = make_shared<Scene>();
    renderer = make_shared<SceneRenderer>(mainLoop->getGlContext(), scene);
    camera   = make_shared<Camera>(Application::DEFAULT_WINDOW_WIDTH, Application::DEFAULT_WINDOW_HEIGHT);
    gui      = make_shared<ApplicationGui>(this);

    // create entities
    auto planet = make_shared<PlanetEntity>();

    scene->setElement("axis",        { vt::types::ColorLinesVT, make_shared<AxisEntity>()});
    scene->setElement("planet",      { vt::types::PlanetElevationVT, planet});
    scene->setElement("planet_data", { vt::types::UndefinedVT, planet});
    renderer->updateScene();

    // init control
    mainLoop->addEventReceiver(make_shared<sdl::SDLOrbitCameraController>(camera)); // comera control
    mainLoop->addEventReceiver(make_shared<ApplicationEventReceiver>(this)); // keyboard input
    mainLoop->addEventReceiver(gui); // gui input

    // bind main loop draw to
    mainLoop->setDrawCallback(bind(&Application::draw, this));

    GPD_LOG_DEBUG("Application initialized.");
    return true;
}

int Application::run()
{
    GPD_LOG_DEBUG("Application running ...");
    mainLoop->run();
    GPD_LOG_DEBUG("Application end.");
    return 0;
}

void Application::draw()
{
    // camera is moved with mainLoop with help of manipulator as event receiver
    renderer->draw(camera);
    gui->draw();
}
