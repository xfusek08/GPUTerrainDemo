
#include <geGL/geGL.h>
#include <geUtil/Text.h>

#include <TerrainDemo/entities/PlanetEntity.h>

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

	if (_texture == nullptr || _textureWarped == nullptr) {
        bool isWarpPrev = _planet->warpTexture;

        _planet->warpTexture = true;
        _textureWarped = loadTextureFromPlanet();

        _planet->warpTexture = false;
        _texture = loadTextureFromPlanet();

        _planet->warpTexture = isWarpPrev;
	};

    if (_planet->warpTexture) {
        _textureWarped->bind(0);
    } else {
        _texture->bind(0);
    }

    _program->set1ui("resolution", _planet->meshResolution);
	_program->set1ui("showCube", _planet->showCube);

    return vaoContainer;
}

shared_ptr<ge::gl::Texture> PlanetCubeMapVT::loadTextureFromPlanet()
{
    unsigned int w = 1000;
	unsigned int h = 1000;

	// move to VAO container or get working texture object
    auto tex = make_shared<ge::gl::Texture>(GL_TEXTURE_CUBE_MAP, GL_RGBA, 0, w, h);
	for (int i = 0; i < 6; ++i) {
		unique_ptr<unsigned char[]> data = _planet->getTextureDataForFace(i, w, h);
        tex->setData2D(
            data.get(),                        // data
            GL_RGBA,                           // format
            GL_UNSIGNED_BYTE,                  // type
            0,                                 // level
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i // target
        );
	}

	tex->texParameteri(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	tex->texParameteri(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	tex->texParameteri(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	tex->texParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	tex->texParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return tex;
}
