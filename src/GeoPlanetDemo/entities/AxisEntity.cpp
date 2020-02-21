
#include <GeoPlanetDemo/entities/AxisEntity.h>
#include <GeoPlanetDemo/vt/VAOContainer.h>
#include <geGL/geGL.h>

using namespace std;
using namespace gpd;
using namespace gpd::entities;

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
        0.6f, 0.2f, 0.2f, // negative x - dark red
        1.f, 0.f, 0.f,      // positive x - red
        0.2f, 0.6f, 0.2f, // negative y - dark green
        0.f, 1.f, 0.f,    // negative y - green
        0.f, 0.f, 1.f,    // negative z - dark blue
        0.5f, 0.5f, 1.f,  // positive z - blue
    };
}
