
#include <memory>

#include <TerrainDemo/core/Log.h>
#include <TerrainDemo/core/Utils.h>
#include <TerrainDemo/core/Scene.h>
#include <TerrainDemo/core/Camera.h>
#include <TerrainDemo/core/SceneRenderer.h>

#include <TerrainDemo/tdsdl/SDLGlMainLoop.h>
#include <TerrainDemo/tdsdl/SDLOrbitCameraController.h>

#include <TerrainDemo/entities/AxisEntity.h>
#include <TerrainDemo/entities/PlanetEntity.h>

#include <TerrainDemo/vt/types.h>

#include <TerrainDemo/Application.h>
#include <TerrainDemo/ApplicationEventReciever.h>

using namespace std;
using namespace TerrainDemo;
using namespace sdl2cpp;

Application::Application() {}

Application::~Application() {}

int Application::init()
{
    TD_LOG_DEBUG("Application initiating ...");

    mainLoop = make_shared<tdsdl::SDLGlMainLoop>(Application::WINDOW_WIDTH, Application::WINDOW_HEIGHT);
    scene    = make_shared<core::Scene>();
    renderer = make_shared<core::SceneRenderer>(mainLoop->getGlContext(), scene);
    camera   = make_shared<core::Camera>(Application::WINDOW_WIDTH, Application::WINDOW_HEIGHT);

	scene->addEntity("axis", make_shared<entities::AxisEntity>(vt::VTType::ColorLinesVT));
    scene->addEntity("planet", make_shared<entities::PlanetEntity>(vt::VTType::PlanetVT));
    renderer->updateScene();

    auto cameraController = make_shared<tdsdl::SDLOrbitCameraController>(camera);
    auto applicationEventReciever = make_shared<ApplicationEventReciever>(this);

    mainLoop->addEventReceiver(cameraController);
    mainLoop->addEventReceiver(applicationEventReciever);
    mainLoop->setDrawCallback(bind(&Application::draw, this)); // TODO: maybe bind renderer draw directly

    TD_LOG_DEBUG("Application initialized.");
    return true;
}

int Application::run()
{
    TD_LOG_DEBUG("Application running ...");
    mainLoop->run();
    TD_LOG_DEBUG("Application end.");
    return 0;
}

void Application::draw()
{
    // camera is moved with mainLoop with help of manipulator as event reciever
    renderer->draw(camera);
}
