#pragma once

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include <GeoPlanetDemo/vt/VTType.h>

namespace gpd
{
    namespace vt
    {
        class VAOContainer;
    }

    namespace entities
    {
        class Entity
        {
        public:
            Entity(vt::VTType vtType);
            ~Entity() {}

            inline vt::VTType getVtType() const { return vtType; }

            virtual std::vector<float>    getVerticies()  const;
            virtual std::vector<unsigned> getIndieces()   const;
            virtual std::vector<float>    getColors()     const { return {}; }

            bool setVtType(vt::VTType type);

        protected:
            vt::VTType vtType;
        };
    } // namespace entities
} // namespace gpd
