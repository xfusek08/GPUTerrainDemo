
#include <TerrainDemo/core/Camera.h>
#include <TerrainDemo/core/Scene.h>
#include <TerrainDemo/core/Entity.h>

#include <TerrainDemo/vt/BaseVisualizationTechnique.h>

#include <geGL/geGL.h>
#include <geUtil/Text.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace TerrainDemo;
using namespace TerrainDemo::vt;
using namespace TerrainDemo::core;

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
    _gl->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void BaseVisualizationTechnique::draw(shared_ptr<Camera> camera)
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
	_bufferContainer.clear();
	_vaoContainer.clear();
}

void BaseVisualizationTechnique::processScene(shared_ptr<Scene> scene)
{
    if (!isInitialized())
        init();

	for (auto entity : scene->getEntities()) {
		if (entity->getVtType() == getType()) {
			_vaoContainer[entity.get()] = processEntityToVao(entity);
		}
	}
}

VAOContainerElement BaseVisualizationTechnique::processEntityToVao(shared_ptr<Entity> entity)
{
	auto vao = make_shared<ge::gl::VertexArray>(_gl->getFunctionTable());
    vao->bind();
    vao->addElementBuffer(newVaoBuffer(entity->getIndieces()));
    vao->addAttrib(newVaoBuffer(entity->getVerticies()), 0, 3, GL_FLOAT);
    vao->unbind();

	VAOContainerElement result;
	result.vao = vao;
	result.indexSize = entity->getIndieces().size();
	return result;
}

void BaseVisualizationTechnique::beforeDraw(shared_ptr<Camera> camera)
{
	if (camera->hasViewChanged()) {
		_program->setMatrix4fv("projectionMatrix", glm::value_ptr(camera->getProjectionMatrix()));
		_program->setMatrix4fv("viewMatrix", glm::value_ptr(camera->getViewMatrix()));
	}
    _program->use();
}

void BaseVisualizationTechnique::drawInternal(shared_ptr<Camera> camera)
{
    for (auto pair: _vaoContainer) {
		VAOContainerElement elem = pair.second;
		elem.vao->bind();
        _gl->glDrawElements(GL_TRIANGLES, elem.indexSize, GL_UNSIGNED_INT, nullptr);
    }
}

void BaseVisualizationTechnique::afterDraw(shared_ptr<Camera> camera)
{
}
