
#include <TerrainDemo/entities/AxisEntity.h>
#include <TerrainDemo/vt/VAOContainer.h>
#include <geGL/geGL.h>

using namespace std;
using namespace TerrainDemo;
using namespace TerrainDemo::entities;

vector<float> AxisEntity::getVerticies() const
{
    return {
        -2.f,  0.f,  0.f,
         2.f,  0.f,  0.f,
         0.f, -2.f,  0.f,
         0.f,  2.f,  0.f,
         0.f,  0.f, -2.f,
         0.f,  0.f,  2.f,
    };
}

vector<unsigned> AxisEntity::getIndieces() const
{
    return {
        0,1,
        2,3,
        4,5
    };
}

vector<float> AxisEntity::getColors() const
{
    return {
        2.f, 0.f, 0.f,
        2.f, 0.f, 0.f,
        0.f, 2.f, 0.f,
        0.f, 2.f, 0.f,
        0.f, 0.f, 2.f,
        0.f, 0.f, 2.f,
    };
}
