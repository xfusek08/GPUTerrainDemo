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

            void upDown(float degree);
            inline void up(float degree = 0) { upDown(-(degree ? degree : speed)); }
            inline void down(float degree = 0) { upDown(degree ? degree : speed); }
            
            void leftRight(float degree);
            inline void left(float degree = 0) { leftRight(degree ? degree : speed); }
            inline void right(float degree = 0) { leftRight(-(degree ? degree : speed)); }

            void zoomIn();
            void zoomOut();
            void zoom(float amount);

            void lookXY(glm::vec2 delta);
        protected:
            void performRotation(float = 0, glm::vec3 = glm::vec3{0,0,0});

            std::shared_ptr<core::Camera> camera;

            float speed;
            float radius;

            void setRadius(float radius);
        };
    }
}
