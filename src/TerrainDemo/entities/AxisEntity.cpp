
#include <TerrainDemo/entities/AxisEntity.h>
#include <TerrainDemo/vt/VAOContainer.h>
#include <geGL/geGL.h>

using namespace std;
using namespace TerrainDemo;
using namespace TerrainDemo::entities;

AxisEntity::AxisEntity(vt::VTType vtType) : Entity(vtType)
{
    _verticies = {
        -2.f,  0.f,  0.f,
         2.f,  0.f,  0.f,
         0.f, -2.f,  0.f,
         0.f,  2.f,  0.f,
         0.f,  0.f, -2.f,
         0.f,  0.f,  2.f,
    };

    _colors = {
        2.f, 0.f, 0.f,
        2.f, 0.f, 0.f,
        0.f, 2.f, 0.f,
        0.f, 2.f, 0.f,
        0.f, 0.f, 2.f,
        0.f, 0.f, 2.f,
    };

    _indicies = {
        0,1,
        2,3,
        4,5
    };
}

void AxisEntity::loadToVaoElement(shared_ptr<vt::VAOContainer> vaoElem)
{
    vaoElem->vao->addElementBuffer(vaoElem->newBuffer(getIndieces()));
    vaoElem->vao->addAttrib(vaoElem->newBuffer(getVerticies()), 0, 3, GL_FLOAT);
	vaoElem->vao->addAttrib(vaoElem->newBuffer(getColors()), 1, 3, GL_FLOAT);
	vaoElem->indexSize = getIndieces().size();
}
