
#include <glm/glm.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include <GeoPlanetDemo/core/OrbitCameraController.h>
#include <GeoPlanetDemo/core/Utils.h>

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

void OrbitCameraController::upDown(float degree) 
{   
    auto zHeight = glm::normalize(camera->getCameraPosition()).y;
    if (degree < 0 && zHeight >= 0.98) {
        return;
    } else if (degree > 0 && zHeight <= -0.98) {
        return;
    }

    performRotation(
        degree,
        glm::normalize(glm::cross(camera->getCameraDirection(), glm::vec3{ 0.f,1.f,0.f }))
    );
    
}

void OrbitCameraController::leftRight(float degree)
{
    performRotation(
        degree,
        glm::vec3(0.f, 1.f, 0.f)
    );
}

void OrbitCameraController::zoomIn()
{
    setRadius(radius * 0.99f);
    performRotation();
}

void OrbitCameraController::zoomOut()
{
    setRadius(radius * 1.01f);
    performRotation();
}

void OrbitCameraController::zoom(float amount)
{
    setRadius(radius + amount / 7);
    performRotation();
}

void OrbitCameraController::setRadius(float radius)
{
    if (radius > 10) {
        this->radius = 10;
    } else if (radius < 1.3f) {
        this->radius = 1.3f;
    } else {
        this->radius = radius;
    }
}

void OrbitCameraController::lookXY(glm::vec2 delta)
{
    up(radius * (delta.y / 2000));
    leftRight(radius * (delta.x / 2000));
}

void OrbitCameraController::performRotation(float angleIncrement, glm::vec3 axis)
{
    auto pos = camera->getCameraPosition();
    if (angleIncrement != 0 || axis == glm::vec3(0)) {
        glm::quat rot = glm::angleAxis(angleIncrement, axis);
        pos = glm::conjugate(rot) * pos * rot;
    }
    pos = glm::normalize(pos) * radius;
    // GPD_LOG_DEBUG("Camera position: " << pos.x << " " << pos.y << " " << pos.z);
    camera->setCameraPosition(pos);
}
