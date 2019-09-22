#pragma once

#include <memory>

#include <TerrainDemo/vt/types.h>
#include <TerrainDemo/vt/BaseVisualizationTechnique.h>
#include <TerrainDemo/vt/ColorLinesVT.h>
#include <TerrainDemo/vt/PlanetVT.h>
#include <TerrainDemo/vt/PlanetDebugVT.h>

namespace ge
{
	namespace gl
	{
		class Context;
	}
}

namespace TerrainDemo
{
    namespace vt
    {
        class VTFactory
        {
		public:
            static std::shared_ptr<BaseVisualizationTechnique> createVTFromType(std::shared_ptr<ge::gl::Context> context, VTType type)
            {
                switch(type) {
					case VTType::BaseVisualizationTechnique : return std::make_shared<BaseVisualizationTechnique>(context);
					case VTType::ColorLinesVT               : return std::make_shared<ColorLinesVT>(context);
					case VTType::PlanetVT                   : return std::make_shared<PlanetVT>(context);
                    case VTType::PlanetDebugVT              : return std::make_shared<PlanetDebugVT>(context);
					default:
						return nullptr;
                };
            }
        };

    } // namespace vt
} // namespace TerrainDemo
