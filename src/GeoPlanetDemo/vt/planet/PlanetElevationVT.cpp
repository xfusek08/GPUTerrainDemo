
#include <GeoPlanetDemo/core/Utils.h>

#include <GeoPlanetDemo/vt/planet/PlanetElevationVT.h>

using namespace std;
using namespace gpd;
using namespace gpd::vt;
using namespace gp;
using namespace glm;

uvec4 PlanetElevationVT::regionToColor(shared_ptr<Region> region)
{
    auto attr = region->getAttribute(RegionAttributeType::Elevation);
    if (attr.isValid) {
        auto elevation = attr.data.scalar;
        uvec4 baseColor;
        uvec4 mixColor;
        if (elevation < 0) {
            baseColor = uvec4(107, 193, 255, 0);
            elevation = -elevation;
        } else {
            baseColor = uvec4(255, 189, 97, 0);
        }
        return mix(baseColor, uvec4(0,0,0,0), elevation / 4);
    }
    return uvec4(255, 255, 255, 0);
}
