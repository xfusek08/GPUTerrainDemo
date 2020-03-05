#pragma once

#include <memory>

#include <glm/glm.hpp>

namespace ge
{
    namespace util
    {
        class OrbitManipulator;
    }
}

namespace gpd
{
    namespace core
    {
        class Camera
        {
        public:
            // methods
            Camera(
                float viewWidth,
                float viewHeight,
                glm::vec3 position = glm::vec3{ 0, 0, 0 },
                float fov = 30.f,
                float nearPlaneDistance = 0.1f,
                float farPlaneDistace = 1000.f
            );

            // flags
            inline bool hasViewChanged() const { return viewChanged || !changeAccepted; }
            inline void setViewChanged() { viewChanged = true; changeAccepted = false; }
            inline void acceptChange()   { changeAccepted = true; }

            // matrices
            glm::mat4 getViewMatrix();
            inline glm::mat4 getProjectionMatrix() const { return projectionMatrix; }

            // vectors
            inline glm::vec3 getCameraPosition()  const { return position; }
            inline glm::vec3 getTargetPosition()  const { return target; }
            inline glm::vec3 getUpVector()        const { return up; }
            inline glm::vec3 getCameraDirection() const { return position - target;  }

            inline void setCameraPosition(glm::vec3 position)                { this->position = position; setViewChanged(); }
            inline void setTargetPosition(glm::vec3 target)                  { this->target = target;     setViewChanged(); }
            inline void setUpVector(glm::vec3 up)                            { this->up = up;             setViewChanged(); }
            inline void setViewSize(unsigned int width, unsigned int height) { this->viewWidth = width; this->viewHeight = height; updateProjectionMatrix(); setViewChanged(); }
            inline void setViewSize(glm::uvec2 newSize)                      { setViewSize(newSize.x, newSize.y); }

            // projection scalars
            inline float getFov() const { return fov; }
            inline float getNearPlaneDistance() const { return nearPlane; }
            inline float getFarPlaneDistance() const { return farPlane; }

        protected:
            // properties

            // flags
            bool viewChanged    = true;
            bool changeAccepted = false;

            glm::mat4 viewMatrix;
            glm::mat4 projectionMatrix;

            // projection details
            float viewWidth  = 0.f;
            float viewHeight = 0.f;
            float fov        = 0.f;
            float nearPlane  = 0.f;
            float farPlane   = 0.f;

            // view details
            glm::vec3 position;
            glm::vec3 target;
            glm::vec3 up;

            // methods
            void updateViewMatrix();
            void updateProjectionMatrix();
        };

    }; // namespace core
} // namespace gpd
