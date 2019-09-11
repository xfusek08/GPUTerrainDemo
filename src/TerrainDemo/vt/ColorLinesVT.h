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

			inline VTType getType() const override { return VTType::ColorLinesVT; }

		protected:
            void initGlProgram() override;
			VAOContainerElement processEntityToVao(std::shared_ptr<entities::Entity> entity) override;
			void drawInternal(std::shared_ptr<core::Camera> camera) override;
        };
    } // namespace vt
} // namespace TerrainDemo