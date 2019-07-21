
#include <TerrainDemo/TerrainVT.h>
#include <TerrainDemo/core/Utils.h>

#include <geUtil/Text.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace ge::gl;
using namespace TerrainDemo;
using namespace TerrainDemo::core;
using namespace TerrainDemo::interfaces;

TerrainVT::TerrainVT()
{
}

void TerrainVT::drawSetUp()
{
    // initiation of gl
    gl->glEnable(GL_DEPTH_TEST);
    gl->glDepthFunc(GL_LEQUAL);
    gl->glDisable(GL_CULL_FACE);
    gl->glClearColor(0, 0, 0, 0);

    // create and conpile program
    program = make_shared<ge::gl::Program>(
        make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, ge::util::loadTextFile(VERTEX_SHADER)),
        make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, ge::util::loadTextFile(FRAGMENT_SHADER))
    );

    program->setMatrix4fv("projectionMatrix", glm::value_ptr(_camera->getProjectionMatrix()));

    if (_scene != nullptr) {
        for (shared_ptr<Entity> entity : _scene->getEntities()) {
            entity->initVao(gl);
        }
    }
}

void TerrainVT::draw()
{
    gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (!_scene)
        return;

    if (_camera->hasViewChanged())
        program->setMatrix4fv("viewMatrix", glm::value_ptr(_camera->getViewMatrix()));

    program->use();

    for (shared_ptr<Entity> entity : _scene->getEntities()) {
        entity->vao->bind();
        gl->glDrawElements(entity->drawMode, entity->getIndieces().size(), entity->drawType, nullptr);
    }
}

void TerrainVT::setScene(shared_ptr<Scene> scene)
{
    _scene = static_pointer_cast<TerrainScene>(scene);
}
