#pragma once

#include <SDL.h>

#include <TerrainDemo/tdsdl/SDLEventReceiverInterface.h>
#include <TerrainDemo/core/OrbitCameraController.h>

namespace TerrainDemo
{
    namespace tdsdl
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
