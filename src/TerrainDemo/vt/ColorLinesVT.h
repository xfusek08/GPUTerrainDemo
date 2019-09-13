#pragma once

#include <TerrainDemo/vt/BaseVisualizationTechnique.h>
#include <geGL/Generated/OpenGLTypes.h>
#include <geGL/Generated/OpenGLConstants.h>

namespace TerrainDemo
{
    namespace vt
    {
        class ColorLinesVT : public BaseVisualizationTechnique
        {
		public:
			ColorLinesVT(std::shared_ptr<ge::gl::Context> gl) : BaseVisualizationTechnique(gl) {}

			inline VTType getType() const override { return VTType::ColorLinesVT; }
			inline GLenum getDrawMode() const { return GL_LINES; }

		protected:
            void initGlProgram() override;			
        };
    } // namespace vt
} // namespace TerrainDemo