#pragma once

#include <GeoPlanetDemo/vt/VTFactory.h>

#include <GeoPlanetDemo/vt/planet/helper/PlateColorizer.h>

namespace gpd
{
    namespace vt
    {
        class PlanetVectorsVT : public VisualizationTechnique
        {
        public:
            // methods
            PlanetVectorsVT(VTType type, std::shared_ptr<ge::gl::Context> gl) :
                plateColorizer(std::make_shared<helper::PlateColorizer>()),
                VisualizationTechnique(type, gl) {}

        protected:
            // properties
            std::shared_ptr<helper::PlateColorizer> plateColorizer;

            // methods
            void initGl() override;
            void initGlProgram() override;
            std::shared_ptr<VAOContainer> processEntityToVaoContainer(std::shared_ptr<scene::Entity> entity) override;
        };
    } // namespace vt
} // namespace gpd

REGISTER_VT_TYPE(PlanetVectorsVT)
