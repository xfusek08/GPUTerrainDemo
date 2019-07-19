#pragma once
#include <SDL.h>

#include <TerrainDemo/interfaces/ISDLEventReceiver.h>
#include <TerrainDemo/core/Camera.h>

namespace TerrainDemo
{
    namespace tdsdl
    {
        class SDLOrbitCameraController : public interfaces::ISDLEventReceiver
        {
        public:
            SDLOrbitCameraController(std::shared_ptr<core::Camera>);
            inline std::shared_ptr<core::Camera> getCamera() { return _camera; }

            virtual bool processSDLEvent(SDL_Event const&) override;
            virtual void onFrameUpdate() override;

            void up();
            void down();
            void left();
            void right();

            void zoomIn();
            void zoomOut();

            void lookXY(glm::vec2 delta);
        protected:
            void performRotation(float = 0, glm::vec3 = glm::vec3{0,0,0});

            std::shared_ptr<core::Camera> _camera;

            float _speed;
            float _radius;
        };
    }
}
