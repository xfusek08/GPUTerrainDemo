
#include <GeoPlanetDemo/core/Camera.h>

#include <GeoPlanetDemo/vt/planet/PlanetWireFrameVT.h>
#include <GeoPlanetDemo/vt/VAOContainer.h>

#include <GeoPlanetDemo/entities/PlanetEntity.h>
#include <geGL/geGL.h>
#include <geUtil/Text.h>

using namespace std;
using namespace gpd;
using namespace gpd::vt;

void PlanetWireFrameVT::initGlProgram()
{
    PlanetVT::initGlProgram();
    program_faces = program;
    program_lines = make_shared<ge::gl::Program>(
        make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, ge::util::loadTextFile(SHADER_PLANET_VERTEX)),
        make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, ge::util::loadTextFile(SHADER_PLANET_FRAGMENT_LINES))
    );
}

void PlanetWireFrameVT::draw(shared_ptr<core::Camera> camera)
{
    program = program_faces;
    gl->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    beforeDraw(camera);
    drawInternal(camera);
    afterDraw(camera);

    program = program_lines;
    gl->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    beforeDraw(camera);
    drawInternal(camera);
    afterDraw(camera);

    program = program_faces;
}

shared_ptr<VAOContainer> PlanetWireFrameVT::processEntityToVaoContainer(shared_ptr<entities::Entity> entity)
{
    auto res = PlanetVT::processEntityToVaoContainer(entity);
    program_lines->set1ui("resolution", planet->meshResolution);
    return res;
}
