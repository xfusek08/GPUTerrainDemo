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
			inline GLenum getDrawMode() const { return GL_TRIANGLES; }

		protected:
            std::shared_ptr<ge::gl::Program> _program_faces;
            std::shared_ptr<ge::gl::Program> _program_lines;
            void initGlProgram() override;

            virtual void draw(std::shared_ptr<core::Camera> camera) override;
            virtual void drawInternal(std::shared_ptr<core::Camera> camera) override;
        };
    } // namespace vt
} // namespace TerrainDemo