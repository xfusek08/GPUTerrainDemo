
#include <TerrainDemo/entities/PlanetEntity.h>
#include <TerrainDemo/vt/VAOContainer.h>
#include <geGL/geGL.h>

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
    auto gl = vaoElem->vao->getContext();
	unsigned int texture;
	gl.glGenTextures(1, &texture);
	gl.glBindTexture(GL_TEXTURE_2D, texture);
	gl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	gl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	gl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	gl.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char colors[10][10][4];
    for (unsigned char y = 0; y < 10; ++y) {
        for(unsigned char x = 0; x < 10; ++x) {
			unsigned char c = ((x + (10 * y)) * 255) / (10 * 10);
			colors[x][y][0] = c;
			colors[x][y][1] = c;
			colors[x][y][2] = c;
			colors[x][y][3] = 0;
        }
    }

	gl.glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 10, 10, 0, GL_RGBA, GL_UNSIGNED_BYTE, &colors);
	gl.glBindTexture(GL_TEXTURE_2D, texture);
}
