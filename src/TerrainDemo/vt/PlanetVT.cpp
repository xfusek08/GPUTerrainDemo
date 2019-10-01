
#include <TerrainDemo/core/Utils.h>
#include <TerrainDemo/core/Camera.h>

#include <TerrainDemo/vt/VAOContainer.h>
#include <TerrainDemo/vt/PlanetVT.h>
#include <geGL/geGL.h>
#include <geUtil/Text.h>

#include <TerrainLib/PlanetSurface.h>
#include <TerrainLib/PlanetTextureGenerator.h>

using namespace std;
using namespace TerrainDemo;
using namespace TerrainDemo::vt;

void PlanetVT::initGlProgram()
{
    _program = make_shared<ge::gl::Program>(
        make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, ge::util::loadTextFile(SHADER_PLANET_VERTEX)),
        make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, ge::util::loadTextFile(SHADER_PLANET_FRAGMENT))
    );
}

shared_ptr<VAOContainer> PlanetVT::processEntityToVaoContainer(shared_ptr<entities::Entity> entity)
{
	auto vaoContainer = make_shared<VAOContainer>(_gl);
    vaoContainer->vao->bind();

    unsigned int w = 800;
	unsigned int h = 800;

    auto planetTextureGenerator = make_shared<tl::PlanetTextureGenerator>(make_shared<tl::PlanetSurface>());

    auto gl = vaoContainer->vao->getContext();

    // move to VAO container or get working texture object
    unsigned int texture;
	gl.glGenTextures(1, &texture);
	gl.glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

    for (int i = 0; i < 6; ++i) {
        unique_ptr<unsigned char[]> data = planetTextureGenerator->getTextureDataForFace(i, w, h);
        gl.glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.get());
    }

	gl.glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	gl.glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	gl.glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	gl.glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	gl.glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	vaoContainer->vao->unbind();
	return vaoContainer;
}

void PlanetVT::drawInternal(shared_ptr<core::Camera> camera)
{
    uint32_t resolution = 10;

    _program->set1ui("resolution", resolution);

    for (auto pair: _vaoContainerMap) {
		auto elem = pair.second;
		elem->vao->bind();
        _gl->glDrawArrays(GL_TRIANGLES, 0, 6 * 6 * resolution * resolution);
    }
}