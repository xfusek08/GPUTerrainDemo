#pragma once

#define VT_TYPE_LIST \
    BaseVisualizationTechnique, \
    ColorLinesVT, \
    PlanetVT, \
    PlanetDebugVT

namespace TerrainDemo
{
    namespace vt
    {
        enum class VTType {
            VT_TYPE_LIST
        };
    }
}