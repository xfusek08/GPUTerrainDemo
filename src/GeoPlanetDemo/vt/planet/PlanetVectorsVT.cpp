
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

void PlanetVectorsVT::initGl()
{
    VisualizationTechnique::initGl();
    gl->glDisable(GL_CULL_FACE);
}

shared_ptr<VAOContainer> PlanetVectorsVT::processEntityToVaoContainer(shared_ptr<scene::Entity> entity)
{
    auto planet = dynamic_pointer_cast<PlanetEntity>(entity);

    vector<glm::vec3> verticies;
    vector<glm::vec3> colors;
    vector<unsigned int> indices;

    // for now only plate centers
    auto indexCnt = 3 * (
        planet->surface->plates.size()
        + planet->surface->getRegions().size()
    );

    verticies.reserve(indexCnt);
    colors.reserve(indexCnt);
    indices.reserve(indexCnt);

    unsigned int index = 0;
    for (auto plate : planet->surface->plates) {
        float vectorSize = 0.1f;
        float childScale = 0.6f;

        auto origin             = plate->getCenter();
        auto direction          = plate->shiftVector * vectorSize;
        auto destination        = origin + direction;
        auto trinagleBaseOffset = glm::normalize(glm::cross(origin, destination)) * vectorSize  * 0.1f;
        auto uColor             = plateColorizer->plateColor(plate.get());

        auto color  = glm::vec3(
            float(uColor.x) / 255.0,
            float(uColor.y) / 255.0,
            float(uColor.z) / 255.0
        );
        auto darkercolor = glm::mix(color, glm::vec3(0, 0, 0), 0.2);

        // draw general plate vector
        verticies.push_back(origin + trinagleBaseOffset);
        colors.push_back(darkercolor);
        indices.push_back(index++);
        verticies.push_back(origin - trinagleBaseOffset);
        colors.push_back(darkercolor);
        indices.push_back(index++);

        verticies.push_back(destination);
        colors.push_back(color);
        indices.push_back(index++);

        // draw vector for each region
        trinagleBaseOffset *= childScale;
        direction          *= childScale;
        vectorSize         *= childScale;
        color              = glm::mix(color, glm::vec3(1, 1, 1), 0.2);
        darkercolor        = glm::mix(color, glm::vec3(1, 1, 1), 0.2);
        for (auto region : plate->getMemberRegions()) {
            origin = region->position.getGlobal();
            destination = glm::normalize(origin + glm::normalize(direction) * glm::length(plate->shiftVector) * vectorSize);

            verticies.push_back(origin + trinagleBaseOffset);
            colors.push_back(darkercolor);
            indices.push_back(index++);
            verticies.push_back(origin - trinagleBaseOffset);
            colors.push_back(darkercolor);
            indices.push_back(index++);

            verticies.push_back(destination);
            colors.push_back(color);
            indices.push_back(index++);
        }
    }

    auto vaoContainer = make_shared<VAOContainer>(gl);
    vaoContainer->vao->bind();
    vaoContainer->vao->addElementBuffer(vaoContainer->newBuffer(indices));
    vaoContainer->vao->addAttrib(vaoContainer->newBuffer(verticies), 0, 3, GL_FLOAT);
    vaoContainer->vao->addAttrib(vaoContainer->newBuffer(colors), 1, 3, GL_FLOAT);
    vaoContainer->indexSize = indexCnt;
    vaoContainer->vao->unbind();
    return vaoContainer;
}
