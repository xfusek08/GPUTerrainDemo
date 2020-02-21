
#include <GeoPlanetDemo/entities/PlanetEntity.h>

#include <GeoPlanetDemo/vt/planet/PlanetFaceColorVT.h>

using namespace std;
using namespace gpd;
using namespace gpd::entities;
using namespace gpd::vt;
using namespace gp;
using namespace glm;

shared_ptr<VAOContainer> PlanetFaceColorVT::processEntityToVaoContainer(shared_ptr<Entity> entity)
{
    auto r = dynamic_pointer_cast<PlanetEntity>(entity)->getResolution();
    resolutionPerFace = r * r;
    return PlanetVT::processEntityToVaoContainer(entity);
}

uvec4 PlanetFaceColorVT::regionToColor(shared_ptr<Region> region)
{
    uvec4 color = uvec4(255, 255, 255, 0);
    switch (region->position.getFaceID())
    {
        case FACE_FRONT: color = uvec4(71, 220, 54, 0); break;
        case FACE_RIGHT: color = uvec4(220, 54, 76, 0); break;
        case FACE_BACK:  color = uvec4(220, 132, 54, 0); break;
        case FACE_LEFT:  color = uvec4(51, 188, 255, 0); break;
        case FACE_NORTH: color = uvec4(255, 204, 51, 0); break;
        case FACE_SOUTH: color = uvec4(137, 54, 220, 0); break;
    }

    float c = float(region->getID() % resolutionPerFace) / float(resolutionPerFace);
    return mix(color, uvec4(255.0f * vec4(c, c, c, 0)), 0.5);
}
