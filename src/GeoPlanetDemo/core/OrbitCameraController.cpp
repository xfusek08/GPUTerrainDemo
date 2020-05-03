
#include <glm/glm.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include <GeoPlanetDemo/core/OrbitCameraController.h>

using namespace std;
using namespace gpd::core;

OrbitCameraController::OrbitCameraController(shared_ptr<Camera> camera) :
    camera(camera),
    speed(0),
    radius(0)
{
    camera->setCameraPosition(glm::vec3{0,0,1});
    performRotation();
}

void OrbitCameraController::up(float degree)
{
    performRotation(
        (degree ? degree : speed),
        glm::normalize(glm::cross(camera->getCameraDirection(), glm::vec3{ 0.f,1.f,0.f }))
    );
}

void OrbitCameraController::down(float degree)
{
    performRotation(
        -(degree ? degree : speed),
        glm::normalize(glm::cross(camera->getCameraDirection(), glm::vec3{ 0.f,1.f,0.f }))
    );
}

void OrbitCameraController::left(float degree)
{
    performRotation(
        -(degree ? degree : speed),
        glm::vec3(0.f, 1.f, 0.f)
    );
}

void OrbitCameraController::right(float degree)
{
    performRotation(
        (degree ? degree : speed),
        glm::vec3(0.f, 1.f, 0.f)
    );
}

void OrbitCameraController::zoomIn()
{
    radius *= 0.99f;
    performRotation();
}

void OrbitCameraController::zoomOut()
{
    radius *= 1.01f;
    performRotation();
}

void OrbitCameraController::zoom(float amount)
{
    radius += amount / 10;    
    performRotation();
}

void OrbitCameraController::lookXY(glm::vec2 delta)
{    
    down(radius * (delta.y / 2000));
    right(radius * (delta.x / 2000));
}

void OrbitCameraController::performRotation(float angleIncrement, glm::vec3 axis)
{
    auto pos = camera->getCameraPosition();
    if (angleIncrement != 0 || axis == glm::vec3(0)) {
        glm::quat rot = glm::angleAxis(angleIncrement, axis);
        pos = glm::conjugate(rot) * pos * rot;
    }
    pos = glm::normalize(pos) * radius;
    camera->setCameraPosition(pos);
}
