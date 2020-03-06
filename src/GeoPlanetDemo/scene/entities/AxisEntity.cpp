
#include <GeoPlanetDemo/scene/entities/AxisEntity.h>

using namespace std;
using namespace gpd;
using namespace gpd::scene::entities;

const vector<float> AxisEntity::getVerticies() const
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

const vector<unsigned> AxisEntity::getIndieces() const
{
    return {
        0,1,
        2,3,
        4,5
    };
}

const vector<float> AxisEntity::getColors() const
{
    return {
        0.6f, 0.2f, 0.2f, // negative x - dark red
        1.f, 0.f, 0.f,    // positive x - red
        0.2f, 0.6f, 0.2f, // negative y - dark green
        0.f, 1.f, 0.f,    // negative y - green
        0.f, 0.f, 1.f,    // negative z - dark blue
        0.5f, 0.5f, 1.f,  // positive z - blue
    };
}
