
#include <GeoPlanetDemo/scene/Entity.h>

using namespace std;
using namespace gpd;
using namespace gpd::scene;

const vector<float> Entity::getVerticies() const
{
    return {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         0.0f,  1.0f, 0.0f,
    };
}

const vector<unsigned> Entity::getIndieces() const
{
    return {
        0, 1, 2
    };
}

const vector<float> Entity::getColors() const
{
    return {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
    };
}
