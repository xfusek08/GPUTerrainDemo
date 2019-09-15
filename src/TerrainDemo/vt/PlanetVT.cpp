
#include <TerrainDemo/vt/VAOContainer.h>
#include <TerrainDemo/vt/PlanetVT.h>
#include <geGL/geGL.h>
#include <geUtil/Text.h>

using namespace std;
using namespace TerrainDemo;
using namespace TerrainDemo::vt;

void PlanetVT::initGlProgram()
{
    _program = make_shared<ge::gl::Program>(
        make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, ge::util::loadTextFile(SHADER_PLANET_VERTEX)),
        make_shared<ge::gl::Shader>(GL_GEOMETRY_SHADER, ge::util::loadTextFile(SHADER_PLANET_GEOMETRY)),
        make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, ge::util::loadTextFile(SHADER_PLANET_FRAGMENT))
    );
}

void PlanetVT::drawInternal(shared_ptr<core::Camera> camera)
{
    for (auto pair: _vaoContainer) {
		auto elem = pair.second;
		elem->vao->bind();
        _gl->glDrawArrays(getDrawMode(), 0, 6);
    }
}