#pragma once

#include <TerrainDemo/vt/BaseVisualizationTechnique.h>
#include <geGL/Generated/OpenGLTypes.h>
#include <geGL/Generated/OpenGLConstants.h>

namespace TerrainDemo
{
    namespace core
	{
		class Camera;
    }

    namespace vt
    {
        class PlanetVT : public BaseVisualizationTechnique
        {
		public:
			PlanetVT(std::shared_ptr<ge::gl::Context> gl) : BaseVisualizationTechnique(gl) {}

			inline VTType getType() const override { return VTType::PlanetVT; }
			inline GLenum getDrawMode() const override { return GL_TRIANGLES; }

		protected:
			virtual void initGlProgram() override;
            virtual void drawInternal(std::shared_ptr<core::Camera> camera) override;
        };
    } // namespace vt
} // namespace TerrainDemo