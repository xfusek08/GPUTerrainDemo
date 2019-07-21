#pragma once

#include <vector>

#include <TerrainDemo/core/Entity.h>

namespace TerrainDemo
{
    class AxisEntity : public core::Entity
    {
    public:
        AxisEntity();

    protected:
        void defineVaoAttributes() override;
        std::vector<float> _colors;
    };
} // namespace TerrainDemo
