
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
        make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, ge::util::loadTextFile(SHADER_VERT_COLOR_VERTEX)),
        make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, ge::util::loadTextFile(SHADER_VERT_COLOR_FRAGMENT))
    );
}

shared_ptr<VAOContainer> PlanetVectorsVT::processEntityToVaoContainer(shared_ptr<scene::Entity> entity)
{
    auto planet = dynamic_pointer_cast<PlanetEntity>(entity);

    vector<float> verticies;
    vector<float> indices;



    auto vaoContainer = make_shared<VAOContainer>(gl);
    vaoContainer->vao->bind();
    vaoContainer->vao->addElementBuffer(vaoContainer->newBuffer(entity->getIndieces()));
    vaoContainer->vao->addAttrib(vaoContainer->newBuffer(entity->getVerticies()), 0, 3, GL_FLOAT);
    vaoContainer->vao->addAttrib(vaoContainer->newBuffer(entity->getColors()), 1, 3, GL_FLOAT);
    vaoContainer->indexSize = entity->getIndieces().size();
    vaoContainer->vao->unbind();
    return vaoContainer;
}
