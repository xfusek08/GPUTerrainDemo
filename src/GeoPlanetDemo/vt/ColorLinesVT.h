#pragma once

#include <GeoPlanetDemo/vt/VTFactory.h>

namespace gpd
{
    namespace vt
    {
        class ColorLinesVT : public VisualizationTechnique
        {
        public:
            // methods
            ColorLinesVT(VTType type, std::shared_ptr<ge::gl::Context> gl) : VisualizationTechnique(type, gl) {}

            inline GLenum getDrawMode() const { return GL_LINES; }

        protected:
            void initGlProgram() override;
            virtual std::shared_ptr<VAOContainer> processEntityToVaoContainer(std::shared_ptr<entities::Entity> entity) override;
        };
    } // namespace vt
} // namespace gpd

REGISTER_VT_TYPE(ColorLinesVT)
