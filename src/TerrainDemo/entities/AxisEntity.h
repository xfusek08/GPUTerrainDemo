#pragma once

#include <TerrainDemo/entities/Entity.h>

namespace TerrainDemo
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
} // namespace TerrainDemo
