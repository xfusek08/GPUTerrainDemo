#pragma once
#include <SDL.h>

#include <TerrainDemo/interfaces/ISDLEventReceiver.h>
#include <TerrainDemo/core/Camera.h>

namespace TerrainDemo
{
    namespace tdsdl
    {
        class SDLCameraController : public interfaces::ISDLEventReceiver
        {
        public:
            SDLCameraController();


            virtual bool processSDLEvent(SDL_Event const&) override;
            inline virtual void setCamera(std::shared_ptr<core::Camera> camera) { _camera = camera; }
        protected:
            std::shared_ptr<core::Camera> _camera;
        };
    }
}
