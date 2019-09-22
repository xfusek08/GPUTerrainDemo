
#include <TerrainDemo/entities/PlanetEntity.h>
#include <TerrainDemo/vt/VAOContainer.h>
#include <geGL/geGL.h>
#include <TerrainLib/PlanetSurface.h>

using namespace std;
using namespace TerrainDemo;
using namespace TerrainDemo::entities;

PlanetEntity::PlanetEntity(vt::VTType vtType) : Entity(vtType)
{
    _indicies  = {};
    _verticies = {};
}

void PlanetEntity::loadToVaoElement(shared_ptr<vt::VAOContainer> vaoElem)
{
	unsigned int w = 2048 / 4;
	unsigned int h = 1536 / 3;

	auto planetSurface = make_shared<tl::PlanetSurface>();
    auto gl = vaoElem->vao->getContext();

    // move to VAO container or get working texture object
    unsigned int texture;
	gl.glGenTextures(1, &texture);
	gl.glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

    for (int i = 0; i < 6; ++i) {
        unique_ptr<unsigned char[]> data = planetSurface->getTextureDataForFace(i, w, h);
        gl.glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.get());
    }

	gl.glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	gl.glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	gl.glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	gl.glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	gl.glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
