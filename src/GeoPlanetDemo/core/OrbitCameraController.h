#pragma once
#include <SDL.h>
#include <GeoPlanetDemo/core/Camera.h>

namespace gpd
{
    namespace core
    {
        class OrbitCameraController
        {
        public:
            OrbitCameraController(std::shared_ptr<core::Camera>);

            inline std::shared_ptr<core::Camera> getCamera() { return camera; }

            void up(float degree = 0);
            void down(float degree = 0);
            void left(float degree = 0);
            void right(float degree = 0);

            void zoomIn();
            void zoomOut();
            void zoom(float amount);

            void lookXY(glm::vec2 delta);
        protected:
            void performRotation(float = 0, glm::vec3 = glm::vec3{0,0,0});

            std::shared_ptr<core::Camera> camera;

            float speed;
            float radius;
        };
    }
}
