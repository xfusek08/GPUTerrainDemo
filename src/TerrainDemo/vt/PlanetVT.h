#pragma once

#include <TerrainDemo/vt/BaseVisualizationTechnique.h>
#include <TerrainDemo/entities/PlanetEntity.h>
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
        // properties
        protected:
			std::shared_ptr<entities::PlanetEntity> _planet = nullptr;

        // methods
		public:
			PlanetVT(std::shared_ptr<ge::gl::Context> gl) : BaseVisualizationTechnique(gl) {}

			inline VTType getType() const override { return VTType::PlanetVT; }
			inline GLenum getDrawMode() const override { return GL_TRIANGLES; }

			void processScene(std::shared_ptr<core::Scene> scene) override;

		protected:
			virtual void initGlProgram() override;
            virtual std::shared_ptr<VAOContainer> processEntityToVaoContainer(std::shared_ptr<entities::Entity> entity) override;
            virtual void drawInternal(std::shared_ptr<core::Camera> camera) override;
        };
    } // namespace vt
} // namespace TerrainDemo