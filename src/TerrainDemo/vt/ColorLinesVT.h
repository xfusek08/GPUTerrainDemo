#pragma once

#include <TerrainDemo/vt/BaseVisualizationTechnique.h>

namespace TerrainDemo
{
    namespace vt
    {
        class ColorLinesVT : public BaseVisualizationTechnique
        {
		public:				
			ColorLinesVT(std::shared_ptr<ge::gl::Context> gl) : BaseVisualizationTechnique(gl) {}
        protected:
            void initGlProgram() override;
        };
    } // namespace vt
} // namespace TerrainDemo