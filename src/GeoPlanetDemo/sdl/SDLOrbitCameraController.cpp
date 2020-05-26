
#include <GeoPlanetDemo/sdl/SDLOrbitCameraController.h>

using namespace std;
using namespace gpd::sdl;
using namespace gpd::core;

SDLOrbitCameraController::SDLOrbitCameraController(shared_ptr<Camera> camera) :
    OrbitCameraController::OrbitCameraController(camera)
{
    speed = 0.005f;
    radius = 5.f;
    camera->setCameraPosition(glm::vec3{0, 0, 1});
    performRotation();
}

bool SDLOrbitCameraController::processSDLEvent(SDL_Event const& event)
{
    switch (event.type) {
        case SDL_MOUSEMOTION:
            if (event.motion.state & SDL_BUTTON_LEFT) {
                lookXY({event.motion.xrel, event.motion.yrel});
                return true;
            }
            break;
        case SDL_MOUSEWHEEL:
                zoom(-event.wheel.y);
                return true;
            break;
        default: break;
    }
    return false;
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
