
#include <TerrainDemo/AxisEntity.h>

using namespace std;
using namespace TerrainDemo;
using namespace TerrainDemo::core;

AxisEntity::AxisEntity()
{
    drawMode = GL_LINES;

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

void AxisEntity::defineVaoAttributes()
{
    // adding positions and indicies
    Entity::defineVaoAttributes();

    // adding colors
    vao->addAttrib(newVaoBuffer(_colors), 1, 3, GL_FLOAT);
}
