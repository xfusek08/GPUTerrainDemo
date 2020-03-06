#pragma once

#include <map>

#include <glm/glm.hpp>

namespace gp
{
    class TectonicPlate;
}

namespace gpd
{
    namespace vt
    {
        namespace helper
        {
            class PlateColorizer
            {
            public:
                // methods
                PlateColorizer() {}

                glm::uvec4 plateColor(gp::TectonicPlate* plate);
                void reset();

            private:
                // properties
                std::map<gp::TectonicPlate*, glm::uvec4> colorMap;
            };
        } // namespace helper
    } // namespace vt
} // namespace gpd
