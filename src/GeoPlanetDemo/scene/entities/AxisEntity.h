#pragma once

#include <GeoPlanetDemo/scene/Entity.h>

namespace gpd
{
    namespace scene
    {
        namespace entities
        {
            class AxisEntity : public Entity
            {
            public:
                AxisEntity() : Entity() {}

                virtual const std::vector<float>    getVerticies()  const override;
                virtual const std::vector<unsigned> getIndieces()   const override;
                virtual const std::vector<float>    getColors()     const override;
            };
        } // namespace entities
    } // namespace scene
} // namespace gpd
