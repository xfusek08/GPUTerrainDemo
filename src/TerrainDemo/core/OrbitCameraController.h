#pragma once
#include <SDL.h>
#include <TerrainDemo/core/Camera.h>

namespace TerrainDemo
{
    namespace core
    {
        class OrbitCameraController
        {
        public:
            OrbitCameraController(std::shared_ptr<core::Camera>);

            inline std::shared_ptr<core::Camera> getCamera() { return _camera; }

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
