
#include <glm/glm.hpp>

#include <TerrainDemo/core/Utils.h>
#include <TerrainDemo/tdsdl/SDLCameraController.h>

using namespace TerrainDemo::tdsdl;

SDLCameraController::SDLCameraController() : _camera(nullptr)
{}

bool SDLCameraController::processSDLEvent(SDL_Event const& event)
{
    if (_camera == nullptr)
        return false;

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_UP: {

            } return true;
            case SDLK_DOWN: {

            } return true;
            case SDLK_LEFT: {

            } return true;
            case SDLK_RIGHT: {

            } return true;
            default:;
        }
    }

    return false;
}
