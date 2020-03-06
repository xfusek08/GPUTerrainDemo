
#include <GeoPlanetDemo/vt/planet/helper/PlateColorizer.h>

using namespace gpd::vt::helper;
using namespace gp;

glm::uvec4 PlateColorizer::plateColor(TectonicPlate* plate)
{
    if (plate == nullptr) {
        return glm::uvec4(255, 255, 255, 0);
    }

    glm::uvec4 plateColor;
    auto plate_it = colorMap.find(plate);
    if (plate_it != colorMap.end()) {
        plateColor = plate_it->second;
    } else {
        plateColor = glm::uvec4(
            rand() % 255,
            rand() % 255,
            rand() % 255,
            0
        );
        colorMap[plate] = plateColor;
    }

    return colorMap[plate];
}

void PlateColorizer::reset()
{
    colorMap.clear();
}