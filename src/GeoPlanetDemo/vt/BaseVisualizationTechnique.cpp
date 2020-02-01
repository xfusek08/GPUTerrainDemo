
#include <GeoPlanetDemo/core/Camera.h>
#include <GeoPlanetDemo/core/Scene.h>
#include <GeoPlanetDemo/entities/Entity.h>

#include <GeoPlanetDemo/vt/BaseVisualizationTechnique.h>
#include <GeoPlanetDemo/vt/VAOContainer.h>

#include <geGL/geGL.h>
#include <geUtil/Text.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace  gpd;
using namespace gpd::vt;

BaseVisualizationTechnique::BaseVisualizationTechnique(shared_ptr<ge::gl::Context> gl) :
	_gl(gl)
{
}

void BaseVisualizationTechnique::drawSetUp()
{
	initGl();
}

void BaseVisualizationTechnique::init()
{
	initGlProgram();
	_isInitialized = _gl != nullptr && _program != nullptr;
}

void BaseVisualizationTechnique::initGl()
{
    _gl->glEnable(GL_DEPTH_TEST);
    _gl->glDepthFunc(GL_LEQUAL);
    _gl->glEnable(GL_CULL_FACE);
    _gl->glCullFace(GL_BACK);
	_gl->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void BaseVisualizationTechnique::draw(shared_ptr<core::Camera> camera)
{
	beforeDraw(camera);
	drawInternal(camera);
	afterDraw(camera);
}

void BaseVisualizationTechnique::initGlProgram()
{
	_program = make_shared<ge::gl::Program>(
        make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, ge::util::loadTextFile(SHADER_BASIC_VERTEX)),
        make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, ge::util::loadTextFile(SHADER_BASIC_FRAGMENT))
    );
}

void BaseVisualizationTechnique::clean()
{
	_vaoContainerMap.clear();
}

void BaseVisualizationTechnique::processScene(shared_ptr<core::Scene> scene)
{
	if (!isInitialized()) {
		init();
	}

	for (auto entity : scene->getEntities()) {
		if (entity->getVtType() == getType()) {
			_vaoContainerMap[entity.get()] = processEntityToVaoContainer(entity);
		}
	}
}

shared_ptr<VAOContainer> BaseVisualizationTechnique::processEntityToVaoContainer(shared_ptr<entities::Entity> entity)
{
	auto vaoContainer = make_shared<VAOContainer>(_gl);
    vaoContainer->vao->bind();
    vaoContainer->vao->addElementBuffer(vaoContainer->newBuffer(entity->getIndieces()));
    vaoContainer->vao->addAttrib(vaoContainer->newBuffer(entity->getVerticies()), 0, 3, GL_FLOAT);
	vaoContainer->indexSize = entity->getIndieces().size();
    vaoContainer->vao->unbind();
	return vaoContainer;
}

void BaseVisualizationTechnique::beforeDraw(shared_ptr<core::Camera> camera)
{
	if (camera->hasViewChanged()) {
		_program->setMatrix4fv("projectionMatrix", glm::value_ptr(camera->getProjectionMatrix()));
		_program->setMatrix4fv("viewMatrix", glm::value_ptr(camera->getViewMatrix()));
	}
    _program->use();
}

void BaseVisualizationTechnique::drawInternal(shared_ptr<core::Camera> camera)
{
    for (auto pair: _vaoContainerMap) {
		auto elem = pair.second;
		elem->bind();
        _gl->glDrawElements(getDrawMode(), elem->indexSize, GL_UNSIGNED_INT, nullptr);
		elem->unbind();
    }
}

void BaseVisualizationTechnique::afterDraw(shared_ptr<core::Camera> camera)
{
}
