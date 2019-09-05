
#include <memory>

#include <TerrainDemo/core/Log.h>
#include <TerrainDemo/core/Utils.h>
#include <TerrainDemo/core/Camera.h>
#include <TerrainDemo/core/SceneRenderer.h>

#include <TerrainDemo/tdsdl/SDLGlMainLoop.h>
#include <TerrainDemo/tdsdl/SDLOrbitCameraController.h>

#include <TerrainDemo/entities/AxisEntity.h>

#include <TerrainDemo/vt/types.h>

#include <TerrainDemo/Application.h>

using namespace std;
using namespace TerrainDemo;
using namespace sdl2cpp;

Application::Application() {}

Application::~Application() {}

int Application::init()
{
    TD_LOG_DEBUG("Application initiating ...");

    _mainLoop = make_shared<tdsdl::SDLGlMainLoop>();
    _scene    = make_shared<core::Scene>();
    _renderer = make_shared<core::SceneRenderer>(_mainLoop->getGlContext(), _scene);
    _camera   = make_shared<core::Camera>(100, 100);

    auto cameraController = make_shared<tdsdl::SDLOrbitCameraController>(_camera);
    _mainLoop->addEventReceiver(cameraController);
    _mainLoop->setDrawCallback(bind(&Application::draw, this)); // TODO: maybe bind renderer draw directly

    // TODO: set up scene with entities
    _scene->addEntity(make_shared<entities::AxisEntity>(vt::VTType::ColorLinesVT));

    _renderer->updateScene();

    TD_LOG_DEBUG("Application initialized.");
    return true;
}

int Application::run()
{
    TD_LOG_DEBUG("Application running ...");
    _mainLoop->run();
    TD_LOG_DEBUG("Application end.");
    return 0;
}

void Application::draw()
{
    // camera is moved with _mainLoop with help of manipulator as event reciever
    _renderer->draw(_camera);
}
