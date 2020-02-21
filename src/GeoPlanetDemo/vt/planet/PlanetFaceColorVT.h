#pragma once

#include <GeoPlanetDemo/vt/planet/PlanetVT.h>

namespace gpd
{
    namespace entities {
        class PlanetEntity;
    }

    namespace vt
    {
        class PlanetFaceColorVT : public PlanetVT
        {
        public:
            // methods
            PlanetFaceColorVT(VTType type, std::shared_ptr<ge::gl::Context> gl) : PlanetVT(type, gl) {}

            virtual glm::uvec4 regionToColor(std::shared_ptr<gp::Region> region) override;

            virtual std::shared_ptr<VAOContainer> processEntityToVaoContainer(std::shared_ptr<entities::Entity> entity) override;

        private:
            unsigned int resolutionPerFace;
        };
    } // namespace vt
} // namespace gpd

REGISTER_VT_TYPE(PlanetFaceColorVT)
