#pragma once

#include <GeoPlanetDemo/vt/VTFactory.h>

namespace gpd
{
    namespace vt
    {
        class PlanetVectorsVT : public VisualizationTechnique
        {
        public:
            // methods
            PlanetVectorsVT(VTType type, std::shared_ptr<ge::gl::Context> gl) : VisualizationTechnique(type, gl) {}

        protected:
            void initGlProgram() override;
            std::shared_ptr<VAOContainer> processEntityToVaoContainer(std::shared_ptr<scene::Entity> entity) override;
        };
    } // namespace vt
} // namespace gpd

REGISTER_VT_TYPE(PlanetVectorsVT)
