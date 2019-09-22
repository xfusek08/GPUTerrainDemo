
#include <TerrainDemo/core/Camera.h>
#include <TerrainDemo/core/Scene.h>
#include <TerrainDemo/entities/Entity.h>

#include <TerrainDemo/vt/BaseVisualizationTechnique.h>
#include <TerrainDemo/vt/VAOContainer.h>

#include <geGL/geGL.h>
#include <geUtil/Text.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace TerrainDemo;
using namespace TerrainDemo::vt;

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
	_vaoContainer.clear();
}

void BaseVisualizationTechnique::processScene(shared_ptr<core::Scene> scene)
{
    if (!isInitialized())
        init();

	for (auto entity : scene->getEntities()) {
		if (entity->getVtType() == getType()) {
			_vaoContainer[entity.get()] = processEntityToVaoContainer(entity);
		}
	}
}

shared_ptr<VAOContainer> BaseVisualizationTechnique::processEntityToVaoContainer(shared_ptr<entities::Entity> entity)
{
	auto vaoElement = make_shared<VAOContainer>(_gl);
    vaoElement->vao->bind();
    entity->loadToVaoElement(vaoElement);
    vaoElement->vao->unbind();
	return vaoElement;
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
    for (auto pair: _vaoContainer) {
		auto elem = pair.second;
		elem->bind();
        _gl->glDrawElements(getDrawMode(), elem->indexSize, GL_UNSIGNED_INT, nullptr);
		elem->unbind();
    }
}

void BaseVisualizationTechnique::afterDraw(shared_ptr<core::Camera> camera)
{
}
