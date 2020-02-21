
#include <GeoPlanetDemo/core/Camera.h>
#include <GeoPlanetDemo/core/Scene.h>
#include <GeoPlanetDemo/entities/Entity.h>

#include <GeoPlanetDemo/vt/VisualizationTechnique.h>
#include <GeoPlanetDemo/vt/VAOContainer.h>

#include <geGL/geGL.h>
#include <geUtil/Text.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace gpd;
using namespace gpd::vt;

void VisualizationTechnique::drawSetUp()
{
    initGl();
}

void VisualizationTechnique::init()
{
    initGlProgram();
    isInitialized = gl != nullptr && program != nullptr;
}

void VisualizationTechnique::initGl()
{
    gl->glEnable(GL_DEPTH_TEST);
    gl->glDepthFunc(GL_LEQUAL);
    gl->glEnable(GL_CULL_FACE);
    gl->glCullFace(GL_BACK);
    gl->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void VisualizationTechnique::draw(shared_ptr<core::Camera> camera)
{
    beforeDraw(camera);
    drawInternal(camera);
    afterDraw(camera);
}

void VisualizationTechnique::initGlProgram()
{
    program = make_shared<ge::gl::Program>(
        make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, ge::util::loadTextFile(SHADER_BASIC_VERTEX)),
        make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, ge::util::loadTextFile(SHADER_BASIC_FRAGMENT))
    );
}

void VisualizationTechnique::clean()
{
    vaoContainerMap.clear();
}

void VisualizationTechnique::processScene(shared_ptr<core::Scene> scene)
{
    if (!isInitialized) {
        init();
    }

    for (auto entity : scene->getEntities()) {
        if (entity->getVtType() == getType()) {
            vaoContainerMap[entity.get()] = processEntityToVaoContainer(entity);
        }
    }
}

shared_ptr<VAOContainer> VisualizationTechnique::processEntityToVaoContainer(shared_ptr<entities::Entity> entity)
{
    auto vaoContainer = make_shared<VAOContainer>(gl);
    vaoContainer->vao->bind();
    vaoContainer->vao->addElementBuffer(vaoContainer->newBuffer(entity->getIndieces()));
    vaoContainer->vao->addAttrib(vaoContainer->newBuffer(entity->getVerticies()), 0, 3, GL_FLOAT);
    vaoContainer->indexSize = entity->getIndieces().size();
    vaoContainer->vao->unbind();
    return vaoContainer;
}

void VisualizationTechnique::beforeDraw(shared_ptr<core::Camera> camera)
{
    if (camera->hasViewChanged()) {
        program->setMatrix4fv("projectionMatrix", glm::value_ptr(camera->getProjectionMatrix()));
        program->setMatrix4fv("viewMatrix", glm::value_ptr(camera->getViewMatrix()));
    }
    program->use();
}

void VisualizationTechnique::drawInternal(shared_ptr<core::Camera> camera)
{
    for (auto pair: vaoContainerMap) {
        auto elem = pair.second;
        elem->bind();
        gl->glDrawElements(getDrawMode(), elem->indexSize, GL_UNSIGNED_INT, nullptr);
        elem->unbind();
    }
}

void VisualizationTechnique::afterDraw(shared_ptr<core::Camera> camera)
{
}
