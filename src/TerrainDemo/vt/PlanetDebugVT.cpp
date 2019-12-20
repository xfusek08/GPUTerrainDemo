
#include <TerrainDemo/core/Camera.h>

#include <TerrainDemo/vt/PlanetDebugVT.h>
#include <TerrainDemo/vt/VAOContainer.h>

#include <TerrainDemo/entities/PlanetEntity.h>
#include <geGL/geGL.h>
#include <geUtil/Text.h>

using namespace std;
using namespace TerrainDemo;
using namespace TerrainDemo::vt;

void PlanetDebugVT::initGlProgram()
{
	PlanetVT::initGlProgram();
	_program_faces = _program;
    _program_lines = make_shared<ge::gl::Program>(
        make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, ge::util::loadTextFile(SHADER_PLANET_VERTEX)),
        make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, ge::util::loadTextFile(SHADER_PLANET_FRAGMENT_LINES))
    );
}

void PlanetDebugVT::draw(shared_ptr<core::Camera> camera)
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

	_program = _program_faces;
}

shared_ptr<VAOContainer> PlanetDebugVT::processEntityToVaoContainer(shared_ptr<entities::Entity> entity)
{
	auto res = PlanetVT::processEntityToVaoContainer(entity);
	_program_lines->set1ui("resolution", _planet->meshResolution);
	return res;
}