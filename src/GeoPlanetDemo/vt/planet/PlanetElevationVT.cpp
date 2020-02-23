
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
        if (elevation < 0) {    
            baseColor = uvec4(0, 92, 145,0);
            elevation = fabs(elevation);
        } else {
            baseColor = uvec4(139, 69, 19, 0);
        }
        return mix(baseColor, uvec4(255,255,255,0), elevation / 4);
    }
    return uvec4(255, 255, 255, 0);
}
