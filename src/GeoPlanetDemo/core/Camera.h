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

namespace  gpd
{
    namespace core
    {
        class Camera
        {
        public:
            Camera(
                float viewWidth,
                float viewHeight,
                glm::vec3 position = glm::vec3{ 0, 0, 0 },
                float fov = 45.f,
                float nearPlaneDistance = 0.1f,
                float farPlaneDistace = 1000.f
            );

            // flags
            inline bool hasViewChanged() const { return _hasViewChanged || !_changeAccepted; }
			inline void setViewChanged() { _hasViewChanged = true; _changeAccepted = false; }
			inline void acceptChange() { _changeAccepted = true; }

            // matrices
            glm::mat4 getViewMatrix();
            inline glm::mat4 getProjectionMatrix() const { return _projectionMatrix; }

            // vectors
            inline glm::vec3 getCameraPosition()  const { return _position; }
            inline glm::vec3 getTargetPosition()  const { return _target; }
            inline glm::vec3 getUpVector()        const { return _up; }
            inline glm::vec3 getCameraDirection() const { return _position - _target;  }

			inline void setCameraPosition(glm::vec3 position) { _position = position; setViewChanged(); }
            inline void setTargetPosition(glm::vec3 target)   { _target   = target;   setViewChanged(); }
            inline void setUpVector(glm::vec3 up)             { _up       = up;       setViewChanged(); }

            // projection scalars
            inline float getFov() const { return _fov; }
            inline float getNearPlaneDistance() const { return _nearPlane; }
            inline float getFarPlaneDistance() const { return _farPlane; }
        protected:

			void updateViewMatrix();
            void updateProjectionMatrix();

            // flags
            bool _hasViewChanged = true;
			bool _changeAccepted = false;

            glm::mat4 _viewMatrix;
            glm::mat4 _projectionMatrix;

            // projection details
            float _viewWidth  = 0.f;
            float _viewHeight = 0.f;
            float _fov        = 0.f;
            float _nearPlane  = 0.f;
            float _farPlane   = 0.f;

            // view details
            glm::vec3 _position;
            glm::vec3 _target;
            glm::vec3 _up;
        };

    }; // namespace core
} // namespace  gpd
