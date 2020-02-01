
#include <memory>

#include <GeoPlanetDemo/core/Log.h>
#include <GeoPlanetDemo/core/Utils.h>
#include <GeoPlanetDemo/core/Scene.h>
#include <GeoPlanetDemo/core/Camera.h>
#include <GeoPlanetDemo/core/SceneRenderer.h>

#include <GeoPlanetDemo/sdl/SDLGlMainLoop.h>
#include <GeoPlanetDemo/sdl/SDLOrbitCameraController.h>

#include <GeoPlanetDemo/entities/AxisEntity.h>
#include <GeoPlanetDemo/entities/PlanetEntity.h>

#include <GeoPlanetDemo/vt/types.h>

#include <GeoPlanetDemo/Application.h>
#include <GeoPlanetDemo/ApplicationEventReceiver.h>

using namespace std;
using namespace  gpd;
using namespace sdl2cpp;

Application::Application() {}

Application::~Application() {}

int Application::init()
{
    GPD_LOG_DEBUG("Application initiating ...");

    mainLoop = make_shared<sdl::SDLGlMainLoop>(Application::WINDOW_WIDTH, Application::WINDOW_HEIGHT);
    scene    = make_shared<core::Scene>();
    renderer = make_shared<core::SceneRenderer>(mainLoop->getGlContext(), scene);
    camera   = make_shared<core::Camera>(Application::WINDOW_WIDTH, Application::WINDOW_HEIGHT);

	scene->addEntity("axis", make_shared<entities::AxisEntity>(vt::VTType::ColorLinesVT));
    scene->addEntity("planet", make_shared<entities::PlanetEntity>(vt::VTType::PlanetVT));
    renderer->updateScene();

    auto cameraController = make_shared<sdl::SDLOrbitCameraController>(camera);
    auto applicationEventReceiver = make_shared<ApplicationEventReceiver>(this);

    mainLoop->addEventReceiver(cameraController);
    mainLoop->addEventReceiver(applicationEventReceiver);
    mainLoop->setDrawCallback(bind(&Application::draw, this)); // TODO: maybe bind renderer draw directly

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
}
