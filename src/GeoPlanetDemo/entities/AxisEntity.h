#pragma once

#include <GeoPlanetDemo/entities/Entity.h>

namespace  gpd
{
    namespace entities
    {
        class AxisEntity : public entities::Entity
        {
        public:
            AxisEntity(vt::VTType vtType) : Entity(vtType) {}

			virtual std::vector<float>    getVerticies()  const override;
            virtual std::vector<unsigned> getIndieces()   const override;
            virtual std::vector<float>    getColors()     const override;
        };
    } // namespace entities
} // namespace  gpd
