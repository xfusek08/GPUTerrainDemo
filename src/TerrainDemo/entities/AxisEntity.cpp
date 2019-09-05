
#include <TerrainDemo/entities/AxisEntity.h>

using namespace std;
using namespace TerrainDemo;
using namespace TerrainDemo::entities;
using namespace TerrainDemo::core;

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
