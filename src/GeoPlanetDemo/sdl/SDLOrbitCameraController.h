#pragma once

#include <SDL.h>

#include <GeoPlanetDemo/sdl/SDLEventReceiverInterface.h>
#include <GeoPlanetDemo/core/OrbitCameraController.h>

namespace gpd
{
    namespace sdl
    {
        class SDLOrbitCameraController : public core::OrbitCameraController, public SDLEventReceiverInterface
        {
        public:
            SDLOrbitCameraController(std::shared_ptr<core::Camera>);

            virtual bool processSDLEvent(SDL_Event const&) override;
            virtual void onFrameUpdate() override;
        };
    }
}
