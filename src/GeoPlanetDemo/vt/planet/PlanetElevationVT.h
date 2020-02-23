#pragma once

#include <map>

#include <GeoPlanetDemo/vt/planet/PlanetVT.h>

namespace gpd
{
    namespace entities {
        class PlanetEntity;
    }

    namespace vt
    {
        class PlanetElevationVT : public PlanetVT
        {
        public:
            // methods
            PlanetElevationVT(VTType type, std::shared_ptr<ge::gl::Context> gl) : PlanetVT(type, gl) {}

            virtual glm::uvec4 regionToColor(std::shared_ptr<gp::Region> region) override;

        };
    } // namespace vt
} // namespace gpd

REGISTER_VT_TYPE(PlanetElevationVT)
