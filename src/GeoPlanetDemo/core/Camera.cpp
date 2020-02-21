
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GeoPlanetDemo/core/Camera.h>
#include <GeoPlanetDemo/core/Log.h>

using namespace std;

using namespace gpd::core;
using namespace gpd::interfaces;

Camera::Camera(
    float viewWidth,
    float viewHeight,
    glm::vec3 position,
    float fov,
    float nearPlaneDistance,
    float farPlaneDistace
) :
    viewWidth(viewWidth),
    viewHeight(viewHeight),
    position(position),
    fov(fov),
    nearPlane(nearPlaneDistance),
    farPlane(farPlaneDistace),
    target(glm::vec3{ 0.f, 0.f, 0.f }),
    up(glm::vec3 { 0.f, 1.f, 0.f })
{
    updateProjectionMatrix();
    updateViewMatrix();
}

glm::mat4 Camera::getViewMatrix()
{
    if (viewChanged)
        updateViewMatrix();
    return viewMatrix;
}

// PRIVATE =============================================================

void Camera::updateViewMatrix()
{
    viewMatrix = glm::lookAt(position, target, up);
    viewChanged = false;
}

void Camera::updateProjectionMatrix()
{
    projectionMatrix = glm::perspective(
        glm::radians(fov),
        viewWidth / viewHeight,
        nearPlane,
        farPlane
    );
}
