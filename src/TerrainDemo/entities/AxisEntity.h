#pragma once

#include <TerrainDemo/core/Entity.h>

namespace TerrainDemo
{
    namespace entities
    {
        class AxisEntity : public core::Entity
        {
        public:
            AxisEntity(vt::VTType vtType);

        protected:
            std::vector<float> _colors;
        };
    } // namespace entities
} // namespace TerrainDemo
