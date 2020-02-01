#pragma once

#define VT_TYPE_LIST \
    BaseVisualizationTechnique, \
    ColorLinesVT, \
    PlanetVT, \
    PlanetCubeMapVT, \
    PlanetDebugVT

namespace  gpd
{
    namespace vt
    {
        enum class VTType {
            VT_TYPE_LIST
        };
    }
}