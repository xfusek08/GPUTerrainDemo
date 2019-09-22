
#include <TerrainDemo/core/Utils.h>
#include <TerrainDemo/core/Camera.h>

#include <TerrainDemo/vt/VAOContainer.h>
#include <TerrainDemo/vt/PlanetVT.h>
#include <geGL/geGL.h>
#include <geUtil/Text.h>

#include <glm/glm.hpp>

using namespace std;
using namespace TerrainDemo;
using namespace TerrainDemo::vt;

void PlanetVT::initGlProgram()
{
    _program_faces = make_shared<ge::gl::Program>(
        make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, ge::util::loadTextFile(SHADER_PLANET_VERTEX)),
        make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, ge::util::loadTextFile(SHADER_PLANET_FRAGMENT))
    );
    _program_lines = make_shared<ge::gl::Program>(
        make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, ge::util::loadTextFile(SHADER_PLANET_VERTEX)),
        make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, ge::util::loadTextFile(SHADER_PLANET_FRAGMENT_LINES))
    );
    _program = _program_faces;
}

void PlanetVT::draw(shared_ptr<core::Camera> camera)
{
    _program = _program_faces;
    _gl->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	beforeDraw(camera);
	drawInternal(camera);
	afterDraw(camera);

    _program = _program_lines;
	_gl->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	beforeDraw(camera);
	drawInternal(camera);
	afterDraw(camera);
}
void PlanetVT::drawInternal(shared_ptr<core::Camera> camera)
{
    uint32_t resolution = 10;

    _program->set1ui("resolution", resolution);

    for (auto pair: _vaoContainer) {
		auto elem = pair.second;
		elem->vao->bind();
        _gl->glDrawArrays(GL_TRIANGLES, 0, 6 * 6 * resolution * resolution);
    }
}