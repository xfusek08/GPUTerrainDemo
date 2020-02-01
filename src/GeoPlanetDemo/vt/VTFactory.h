#pragma once

#include <memory>

#include <GeoPlanetDemo/vt/types.h>
#include <GeoPlanetDemo/vt/BaseVisualizationTechnique.h>
#include <GeoPlanetDemo/vt/ColorLinesVT.h>
#include <GeoPlanetDemo/vt/PlanetVT.h>
#include <GeoPlanetDemo/vt/PlanetCubeMapVT.h>
#include <GeoPlanetDemo/vt/PlanetDebugVT.h>

namespace ge
{
	namespace gl
	{
		class Context;
	}
}

namespace  gpd
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
					case VTType::PlanetCubeMapVT            : return std::make_shared<PlanetCubeMapVT>(context);
                    case VTType::PlanetDebugVT              : return std::make_shared<PlanetDebugVT>(context);
					default:
						return nullptr;
                };
            }
        };

    } // namespace vt
} // namespace  gpd
