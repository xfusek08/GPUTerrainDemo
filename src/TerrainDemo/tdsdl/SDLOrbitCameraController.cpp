
#include <glm/glm.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include <TerrainDemo/tdsdl/SDLOrbitCameraController.h>

#ifdef GT_DEBUG
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <TerrainDemo/core/Utils.h>
#endif

using namespace std;
using namespace TerrainDemo::tdsdl;
using namespace TerrainDemo::core;

SDLOrbitCameraController::SDLOrbitCameraController(shared_ptr<Camera> camera) :
    _camera(camera),
    _speed(0.0005f),
    _radius(5.f)
{
    _camera->setCameraPosition(glm::vec3{0,0,1});
    performRotation();
}

bool SDLOrbitCameraController::processSDLEvent(SDL_Event const& event)
{
    // per event reaction ... for example change to default position on zero press
    return true;
}

void SDLOrbitCameraController::onFrameUpdate()
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_UP])         up();
    else if (state[SDL_SCANCODE_DOWN])  down();

    if (state[SDL_SCANCODE_LEFT])       left();
    else if (state[SDL_SCANCODE_RIGHT]) right();

    if (state[SDL_SCANCODE_S])          zoomOut();
    else if (state[SDL_SCANCODE_W])     zoomIn();
}

void SDLOrbitCameraController::up()
{
    performRotation(
        _speed,
        glm::normalize(glm::cross(_camera->getCameraDirection(), glm::vec3{ 0.f,1.f,0.f }))
    );
}

void SDLOrbitCameraController::down()
{
    performRotation(
        -_speed,
        glm::normalize(glm::cross(_camera->getCameraDirection(), glm::vec3{ 0.f,1.f,0.f }))
    );
}

void SDLOrbitCameraController::left()
{
    performRotation(
        -_speed,
        glm::vec3(0.f, 1.f, 0.f)
    );
}

void SDLOrbitCameraController::right()
{
    performRotation(
        _speed,
        glm::vec3(0.f, 1.f, 0.f)
    );
}

void SDLOrbitCameraController::zoomIn()
{
    _radius *= 0.99f;
    performRotation();
}

void SDLOrbitCameraController::zoomOut()
{
    _radius *= 1.01f;
    performRotation();
}

void SDLOrbitCameraController::lookXY(glm::vec2 delta)
{
}

void SDLOrbitCameraController::performRotation(float angleIncrement, glm::vec3 axis)
{
    auto pos = _camera->getCameraPosition();
    if (angleIncrement != 0 || axis == glm::vec3(0)) {
        glm::quat rot = glm::angleAxis(angleIncrement, axis);
        pos = glm::conjugate(rot) * pos * rot;
    }
    pos = glm::normalize(pos) * _radius;
    _camera->setCameraPosition(pos);
}
