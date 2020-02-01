#pragma once

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include <GeoPlanetDemo/vt/types.h>

namespace  gpd
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
            Entity(vt::VTType vtType = vt::VTType::BaseVisualizationTechnique);
			~Entity() {}

			inline vt::VTType getVtType() const { return _vtType; }
            inline void setVtType(vt::VTType type) { _vtType = type; }

			virtual std::vector<float>    getVerticies()  const;
            virtual std::vector<unsigned> getIndieces()   const;
            virtual std::vector<float>    getColors()     const { return {}; }

        protected:
            vt::VTType _vtType;
        };
    } // core
} // namespace  gpd
