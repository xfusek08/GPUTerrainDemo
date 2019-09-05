#pragma once

#include <memory>

#include <TerrainDemo/vt/types.h>
#include <TerrainDemo/vt/BaseVisualizationTechnique.h>
#include <TerrainDemo/vt/ColorLinesVT.h>

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
            static std::shared_ptr<BaseVisualizationTechnique> createVTFromType(std::shared_ptr<ge::gl::Context> context, VTType type)
            {
                switch(type) {
					case VTType::BaseVisualizationTechnique : return std::make_shared<BaseVisualizationTechnique>(context);
					case VTType::ColorLinesVT               : return std::make_shared<ColorLinesVT>(context);
					default: 
						return nullptr;
                };
            }
        };

    } // namespace vt
} // namespace TerrainDemo
