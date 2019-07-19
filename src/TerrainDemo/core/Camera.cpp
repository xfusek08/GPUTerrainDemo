
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <TerrainDemo/core/Camera.h>
#include <TerrainDemo/core/Log.h>

using namespace std;

using namespace TerrainDemo::core;
using namespace TerrainDemo::interfaces;

Camera::Camera(
    float viewWidth,
    float viewHeight,
    glm::vec3 position,
    float fov,
    float nearPlaneDistance,
    float farPlaneDistace
) :
    _viewWidth(viewWidth),
    _viewHeight(viewHeight),
    _position(position),
    _fov(fov),
    _nearPlane(nearPlaneDistance),
    _farPlane(farPlaneDistace),
    _target(glm::vec3{ 0.f, 0.f, 0.f }),
    _up(glm::vec3 { 0.f, 1.f, 0.f })
{
    updateProjectionMatrix();
    updateViewMatrix();
}

glm::mat4 Camera::getViewMatrix()
{
    if (hasViewChanged())
        updateViewMatrix();
    return _viewMatrix;
}

// PRIVATE =============================================================

void Camera::updateViewMatrix()
{
    GPTR_LOG_Debug("Update view matrix.");
    _viewMatrix = glm::lookAt(_position, _target, _up);
    _hasViewChanged = false;
}

void Camera::updateProjectionMatrix()
{
    _projectionMatrix = glm::perspective(
        glm::radians(_fov),
        _viewWidth / _viewHeight,
        _nearPlane,
        _farPlane
    );
}
