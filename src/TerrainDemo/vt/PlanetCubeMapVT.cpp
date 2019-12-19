
#include <geGL/geGL.h>
#include <geUtil/Text.h>

#include <TerrainDemo/entities/PlanetCubeMapEntity.h>

#include <TerrainDemo/vt/VAOContainer.h>
#include <TerrainDemo/vt/PlanetCubeMapVT.h>

using namespace std;
using namespace TerrainDemo;
using namespace TerrainDemo::vt;
using namespace TerrainDemo::entities;

void PlanetCubeMapVT::initGlProgram()
{
    _program = make_shared<ge::gl::Program>(
        make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, ge::util::loadTextFile(SHADER_PLANET_VERTEX)),
        make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, ge::util::loadTextFile(SHADER_PLANET_FRAGMENT_CUBE_MAP))
    );
}

shared_ptr<VAOContainer> PlanetCubeMapVT::processEntityToVaoContainer(shared_ptr<Entity> entity)
{
    auto vaoContainer = make_shared<VAOContainer>(_gl);
    _planet = dynamic_pointer_cast<PlanetEntity>(entity);
    _program->set1ui("resolution", _planet->getMeshResolution());

	/// move to VAO container or get working texture object

    auto cubeMapPlanet = dynamic_pointer_cast<PlanetCubeMapEntity>(_planet);

    unsigned int texture;
	unsigned int w = 1000;
	unsigned int h = 1000;

	_gl->glGenTextures(1, &texture);
	_gl->glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

    for (int i = 0; i < 6; ++i) {
        unique_ptr<unsigned char[]> data = cubeMapPlanet->getTextureDataForFace(i, w, h);
        _gl->glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.get());
    }

	_gl->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	_gl->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	_gl->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	_gl->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	_gl->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return vaoContainer;
}
