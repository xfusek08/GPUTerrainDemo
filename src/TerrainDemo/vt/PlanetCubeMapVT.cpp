
#include <geGL/geGL.h>
#include <geUtil/Text.h>

#include <TerrainDemo/vt/PlanetCubeMapVT.h>

using namespace std;
using namespace TerrainDemo;
using namespace TerrainDemo::vt;
using namespace TerrainDemo::entities;

void PlanetCubeMapVT::initGlProgram()
{
    _program = make_shared<ge::gl::Program>(
        make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, ge::util::loadTextFile(SHADER_PLANET_VERTEX)),
        make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, ge::util::loadTextFile(SHADER_PLANET_FRAGMENT))
    );
}

shared_ptr<VAOContainer> PlanetCubeMapVT::processEntityToVaoContainer(shared_ptr<Entity> entity)
{
    return PlanetVT::processEntityToVaoContainer(entity);
	// _planet = dynamic_pointer_cast<PlanetCubeMapEntity>(entity);

    // auto vaoContainer = make_shared<VAOContainer>(_gl);
	// _program->set1ui("resolution", _planet->getMeshResolution());
    // return vaoContainer;
}
