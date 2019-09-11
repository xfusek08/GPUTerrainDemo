
#include <TerrainDemo/entities/Entity.h>
#include <TerrainDemo/entities/AxisEntity.h>
#include <TerrainDemo/vt/ColorLinesVT.h>
#include <geGL/geGL.h>
#include <geUtil/Text.h>

using namespace std;
using namespace TerrainDemo;
using namespace TerrainDemo::vt;

void ColorLinesVT::initGlProgram()
{
    _program = make_shared<ge::gl::Program>(
        make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, ge::util::loadTextFile(SHADER_VERT_COLOR_VERTEX)),
        make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, ge::util::loadTextFile(SHADER_VERT_COLOR_FRAGMENT))
    );
}

VAOContainerElement ColorLinesVT::processEntityToVao(shared_ptr<entities::Entity> entity)
{
	auto vao = make_shared<ge::gl::VertexArray>(_gl->getFunctionTable());
	auto colorLineEntity = dynamic_pointer_cast<entities::AxisEntity>(entity);
    vao->bind();
    vao->addElementBuffer(newVaoBuffer(colorLineEntity->getIndieces()));
    vao->addAttrib(newVaoBuffer(colorLineEntity->getVerticies()), 0, 3, GL_FLOAT);
	vao->addAttrib(newVaoBuffer(colorLineEntity->getColors()), 1, 3, GL_FLOAT);
	vao->unbind();

	VAOContainerElement result;
	result.vao = vao;
	result.indexSize = entity->getIndieces().size();
	return result;
}

void ColorLinesVT::drawInternal(shared_ptr<core::Camera> camera)
{
    for (auto pair: _vaoContainer) {
		VAOContainerElement elem = pair.second;
		elem.vao->bind();
        _gl->glDrawElements(GL_LINES, elem.indexSize, GL_UNSIGNED_INT, nullptr);
    }
}
