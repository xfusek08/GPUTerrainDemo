
#include <geGL/geGL.h>
#include <geUtil/Text.h>

#include <GeoPlanetDemo/core/Utils.h>
#include <GeoPlanetDemo/core/Camera.h>

#include <GeoPlanetDemo/entities/PlanetEntity.h>

#include <GeoPlanetDemo/vt/VAOContainer.h>
#include <GeoPlanetDemo/vt/planet/PlanetVT.h>

using namespace std;
using namespace gpd;
using namespace gpd::vt;
using namespace gpd::entities;

void PlanetVT::initGlProgram()
{
    program = make_shared<ge::gl::Program>(
        make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, ge::util::loadTextFile(SHADER_PLANET_VERTEX)),
        make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, ge::util::loadTextFile(SHADER_PLANET_FRAGMENT))
    );
}

void PlanetVT::processScene(std::shared_ptr<core::Scene> scene)
{
    VisualizationTechnique::processScene(scene);
}

shared_ptr<VAOContainer> PlanetVT::processEntityToVaoContainer(shared_ptr<Entity> entity)
{
    planet = dynamic_pointer_cast<PlanetEntity>(entity);
    auto regions = planet->getRegions();
    vector<float> regionBuffer = {};
    for (auto region : regions) {

        auto pos   = region->position.getGlobal();
        auto color = regionToColor(region);

        regionBuffer.push_back(pos.x);
        regionBuffer.push_back(pos.y);
        regionBuffer.push_back(pos.z);
        regionBuffer.push_back(0);
        regionBuffer.push_back(color.r / 255.0);
        regionBuffer.push_back(color.g / 255.0);
        regionBuffer.push_back(color.b / 255.0);
        regionBuffer.push_back(0);
    }

    auto vaoContainer = make_shared<VAOContainer>(gl);
    program->set1ui("resolution", planet->meshResolution);
    program->set1ui("showCube", planet->showCube);

    program->set1ui("regionResolution", planet->getResolution());
    program->bindBuffer("regionBuffer", vaoContainer->newBuffer(regionBuffer));

    GPD_LOG_DEBUG("resolution: " << planet->meshResolution);
    GPD_LOG_DEBUG("regionResolution: " << planet->getResolution());
    GPD_LOG_DEBUG("regionBufferSize: " << regionBuffer.size());
    return vaoContainer;
}

glm::uvec4 PlanetVT::regionToColor(shared_ptr<gp::Region> region)
{
    auto color = region->attributes[gp::RegionAttributeType::Color].data.uVector3;
    return glm::uvec4(color.x, color.y, color.z, 0);
}

void PlanetVT::drawInternal(shared_ptr<core::Camera> camera)
{
    for (auto pair: vaoContainerMap) {
        auto elem = pair.second;
        elem->vao->bind();
        gl->glDrawArrays(GL_TRIANGLES, 0, 6 * 6 * planet->meshResolution * planet->meshResolution);
    }
}
