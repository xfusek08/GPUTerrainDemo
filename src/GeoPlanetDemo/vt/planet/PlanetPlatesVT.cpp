
#include <GeoPlanetLib/TectonicPlate.h>

#include <GeoPlanetDemo/vt/planet/PlanetPlatesVT.h>

using namespace std;
using namespace gpd;
using namespace gpd::vt;
using namespace gp;
using namespace glm;

uvec4 PlanetPlatesVT::regionToColor(shared_ptr<Region> region)
{
    auto reg_it = regionColorMap.find(region->getID());
    if (reg_it != regionColorMap.end()) {
        return reg_it->second;
    }

    auto plate = TectonicPlate::getPlateOfRegion(region);    
    auto plateColor = plateColorizer->plateColor(plate); 

    if (plate == nullptr) {
        regionColorMap[region->getID()] = plateColor;
    } else {
        for (auto plateRegion : plate->getMemberRegions()) {
            regionColorMap[plateRegion->getID()] = glm::mix(plateColor, glm::uvec4(255, 255, 255, 0), 0.5);
        }

        for (auto plateRegion : plate->getEdgeRegions()) {
            regionColorMap[plateRegion->getID()] = plateColor;
        }
    }

    return regionColorMap[region->getID()];
}

void PlanetPlatesVT::clean()
{
    PlanetVT::clean();
    regionColorMap.clear();
}
