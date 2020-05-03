
#include <geGL/geGL.h>
#include <geUtil/Text.h>

#include <GeoPlanetDemo/vt/VAOContainer.h>
#include <GeoPlanetDemo/vt/planet/PlanetCubeMapVT.h>

using namespace std;
using namespace gpd;
using namespace gpd::vt;
using namespace gpd::scene;
using namespace gpd::scene::entities;

void PlanetCubeMapVT::initGlProgram()
{
    program = make_shared<ge::gl::Program>(
        make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, ge::util::loadTextFile(SHADER_PLANET_VERTEX)),
        make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, ge::util::loadTextFile(SHADER_PLANET_CALCULATESPHEREVERTEX)),
        make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, ge::util::loadTextFile(SHADER_PLANET_FRAGMENT_CUBE_MAP))
    );
}

shared_ptr<VAOContainer> PlanetCubeMapVT::processEntityToVaoContainer(shared_ptr<Entity> entity)
{
    auto vaoContainer = make_shared<VAOContainer>(gl);
    auto planet = dynamic_pointer_cast<PlanetEntity>(entity);

    if (texture == nullptr || textureWarped == nullptr) {
        bool isWarpPrev = planet->doWarp;

        planet->doWarp = true;
        textureWarped = loadTextureFromPlanet(planet);

        planet->doWarp = false;
        texture = loadTextureFromPlanet(planet);

        planet->doWarp = isWarpPrev;
    };

    if (planet->doWarp) {
        textureWarped->bind(0);
    } else {
        texture->bind(0);
    }

    program->set1ui("resolution", planet->meshResolution);
    program->set1ui("showCube", planet->showCube);

    return vaoContainer;
}

shared_ptr<ge::gl::Texture> PlanetCubeMapVT::loadTextureFromPlanet(shared_ptr<PlanetEntity> planet)
{
    unsigned int w = 1000;
    unsigned int h = 1000;

    auto tex = make_shared<ge::gl::Texture>(GL_TEXTURE_CUBE_MAP, GL_RGBA, 0, w, h);
    for (int i = 0; i < 6; ++i) {
        unique_ptr<unsigned char[]> data = planet->getTextureDataForFace(i, w, h);
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
