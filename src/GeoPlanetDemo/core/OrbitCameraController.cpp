
#include <glm/glm.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include <GeoPlanetDemo/core/OrbitCameraController.h>

#ifdef GPD_DEBUG
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <GeoPlanetDemo/core/Utils.h>
#endif

using namespace std;
using namespace gpd::core;

OrbitCameraController::OrbitCameraController(shared_ptr<Camera> camera) :
    _camera(camera),
    _speed(0),
    _radius(0)
{
    _camera->setCameraPosition(glm::vec3{0,0,1});
    performRotation();
}

void OrbitCameraController::up()
{
    performRotation(
        _speed,
        glm::normalize(glm::cross(_camera->getCameraDirection(), glm::vec3{ 0.f,1.f,0.f }))
    );
}

void OrbitCameraController::down()
{
    performRotation(
        -_speed,
        glm::normalize(glm::cross(_camera->getCameraDirection(), glm::vec3{ 0.f,1.f,0.f }))
    );
}

void OrbitCameraController::left()
{
    performRotation(
        -_speed,
        glm::vec3(0.f, 1.f, 0.f)
    );
}

void OrbitCameraController::right()
{
    performRotation(
        _speed,
        glm::vec3(0.f, 1.f, 0.f)
    );
}

void OrbitCameraController::zoomIn()
{
    _radius *= 0.99f;
    performRotation();
}

void OrbitCameraController::zoomOut()
{
    _radius *= 1.01f;
    performRotation();
}

void OrbitCameraController::lookXY(glm::vec2 delta)
{
}

void OrbitCameraController::performRotation(float angleIncrement, glm::vec3 axis)
{
    auto pos = _camera->getCameraPosition();
    if (angleIncrement != 0 || axis == glm::vec3(0)) {
        glm::quat rot = glm::angleAxis(angleIncrement, axis);
        pos = glm::conjugate(rot) * pos * rot;
    }
    pos = glm::normalize(pos) * _radius;
    _camera->setCameraPosition(pos);
}
