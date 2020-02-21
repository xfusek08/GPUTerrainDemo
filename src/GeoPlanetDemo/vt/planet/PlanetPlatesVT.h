#pragma once

#include <map>

#include <GeoPlanetDemo/vt/planet/PlanetVT.h>

namespace gp
{
    class TectonicPlate;
}

namespace gpd
{
    namespace core
    {
        class Camera;
    }

    namespace entities {
        class PlanetEntity;
    }

    namespace vt
    {
        class PlanetPlatesVT : public PlanetVT
        {
        public:
            // methods
            PlanetPlatesVT(VTType type, std::shared_ptr<ge::gl::Context> gl) : PlanetVT(type, gl) {}

            virtual glm::uvec4 regionToColor(std::shared_ptr<gp::Region> region) override;
            virtual void clean() override;

        private:
            // properties
            std::map<gp::RegionID, glm::uvec4> regionColorMap;
            std::map<gp::TectonicPlate*, glm::uvec4> plateColorMap;

        };
    } // namespace vt
} // namespace gpd

REGISTER_VT_TYPE(PlanetPlatesVT)
