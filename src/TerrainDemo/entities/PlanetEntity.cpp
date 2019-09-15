
#include <TerrainDemo/entities/PlanetEntity.h>
#include <TerrainDemo/vt/VAOContainer.h>
#include <geGL/geGL.h>

using namespace std;
using namespace TerrainDemo;
using namespace TerrainDemo::entities;

PlanetEntity::PlanetEntity(vt::VTType vtType) : Entity(vtType)
{
    _indicies = {};

    // for now each vertex is one face
    _verticies = {
         0.f,  0.f,  1.f,
         0.f,  0.f, -1.f,
         0.f,  1.f,  0.f,
         0.f, -1.f,  0.f,
         1.f,  0.f,  0.f,
        -1.f,  0.f,  0.f,
    };
}

void PlanetEntity::loadToVaoElement(shared_ptr<vt::VAOContainer> vaoElem)
{
    vaoElem->vao->addAttrib(vaoElem->newBuffer(getVerticies()), 0, 3, GL_FLOAT);
}
