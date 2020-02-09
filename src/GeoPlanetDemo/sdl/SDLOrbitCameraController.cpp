
#include <GeoPlanetDemo/sdl/SDLOrbitCameraController.h>

using namespace std;
using namespace gpd::sdl;
using namespace gpd::core;

SDLOrbitCameraController::SDLOrbitCameraController(shared_ptr<Camera> camera) :
    OrbitCameraController::OrbitCameraController(camera)
{
    _speed = 0.005f;
    _radius = 5.f;
    _camera->setCameraPosition(glm::vec3{ 0,0,1 });
    performRotation();
}

bool SDLOrbitCameraController::processSDLEvent(SDL_Event const& event)
{
    return false;
}

void SDLOrbitCameraController::onFrameUpdate()
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_UP])         down();
    else if (state[SDL_SCANCODE_DOWN])  up();

    if (state[SDL_SCANCODE_LEFT])       right();
    else if (state[SDL_SCANCODE_RIGHT]) left();

    if (state[SDL_SCANCODE_S])          zoomOut();
    else if (state[SDL_SCANCODE_W])     zoomIn();
}