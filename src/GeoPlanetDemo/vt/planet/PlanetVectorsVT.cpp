
#include <geGL/geGL.h>
#include <geUtil/Text.h>

#include <GeoPlanetDemo/scene/entities/PlanetEntity.h>

#include <GeoPlanetDemo/vt/VAOContainer.h>
#include <GeoPlanetDemo/vt/planet/PlanetVectorsVT.h>

using namespace std;
using namespace gpd;
using namespace gpd::vt;
using namespace gpd::scene;
using namespace gpd::scene::entities;

void PlanetVectorsVT::initGlProgram()
{
    program = make_shared<ge::gl::Program>(
        make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, ge::util::loadTextFile(SHADER_PLANET_VECTORS_VERTEX)),
        make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, ge::util::loadTextFile(SHADER_PLANET_VECTORS_FRAGMENT))
    );
}

shared_ptr<VAOContainer> PlanetVectorsVT::processEntityToVaoContainer(shared_ptr<scene::Entity> entity)
{
    auto planet = dynamic_pointer_cast<PlanetEntity>(entity);

    vector<float> verticies;
    vector<float> colors;
    vector<unsigned int> indices;

    // for now only plate centers
    auto indexCnt = planet->getSurface()->plates.size() * 2;

    verticies.reserve(indexCnt * 3);
    verticies.reserve(indexCnt * 3);
    indices.reserve(indexCnt);

    unsigned int index = 0;
    for (auto plate : planet->getSurface()->plates) {
        // origin
        verticies.push_back(0);
        verticies.push_back(0);
        verticies.push_back(0);

        colors.push_back(0);
        colors.push_back(0);
        colors.push_back(0);

        indices.push_back(index++);

        // plate center
        verticies.push_back(plate->center.x);
        verticies.push_back(plate->center.y);
        verticies.push_back(plate->center.z);

        // plate colors
        auto color = plateColorizer->plateColor(plate.get());
        colors.push_back(float(color.x) / 255.0f);
        colors.push_back(float(color.y) / 255.0f);
        colors.push_back(float(color.z) / 255.0f);

        indices.push_back(index++);
    }

    auto vaoContainer = make_shared<VAOContainer>(gl);
    vaoContainer->vao->bind();
    vaoContainer->vao->addElementBuffer(vaoContainer->newBuffer(indices));
    vaoContainer->vao->addAttrib(vaoContainer->newBuffer(verticies), 0, 3, GL_FLOAT);
    vaoContainer->vao->addAttrib(vaoContainer->newBuffer(colors), 1, 3, GL_FLOAT);
    vaoContainer->indexSize = indices.size();
    vaoContainer->vao->unbind();
    return vaoContainer;
}
