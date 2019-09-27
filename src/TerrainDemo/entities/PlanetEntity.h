#pragma once

#include <TerrainDemo/entities/Entity.h>

namespace TerrainDemo
{
    namespace entities
    {
        class PlanetEntity : public entities::Entity
        {
        public:
            PlanetEntity(vt::VTType vtType) : Entity(vtType) {}

            virtual std::vector<float>    getVerticies()  const override { return {}; }
            virtual std::vector<unsigned> getIndieces()   const override { return {}; }
            virtual std::vector<float>    getColors()     const override { return {}; }
        };
    } // namespace entities
} // namespace TerrainDemo
