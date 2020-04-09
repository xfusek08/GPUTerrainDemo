
#include <geGL/geGL.h>
#include <geUtil/Text.h>

#include <GeoPlanetDemo/scene/entities/PlanetEntity.h>

#include <GeoPlanetDemo/vt/VAOContainer.h>
#include <GeoPlanetDemo/vt/planet/PlanetWireFrameVT.h>

using namespace std;
using namespace gpd;
using namespace gpd::vt;
using namespace gpd::scene::entities;

void PlanetWireFrameVT::initGlProgram()
{
    program = make_shared<ge::gl::Program>(
        make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, ge::util::loadTextFile(SHADER_PLANET_VERTEX)),
        make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, ge::util::loadTextFile(SHADER_PLANET_CALCULATESPHEREVERTEX)),
        make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, ge::util::loadTextFile(SHADER_PLANET_FRAGMENT_LINES))
    );
}

void PlanetWireFrameVT::initGl()
{
    VisualizationTechnique::initGl();
    gl->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

shared_ptr<VAOContainer> PlanetWireFrameVT::processEntityToVaoContainer(shared_ptr<scene::Entity> entity)
{
    auto planet = dynamic_pointer_cast<PlanetEntity>(entity);
    auto vaoContainer = make_shared<VAOContainer>(gl);
    program->set1ui("resolution", planet->meshResolution);
    program->set1ui("showCube", planet->showCube);
    numberOfVerticies = 6 * 6 * planet->meshResolution * planet->meshResolution;
    return vaoContainer;
}
