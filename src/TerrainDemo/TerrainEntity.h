#pragma once

#include <memory>

#include <TerrainLib/Terrain.h>

#include <TerrainDemo/core/Entity.h>

namespace TerrainDemo
{
    class TerrainEntity : public core::Entity
    {
    public:
        TerrainEntity();
    protected:
        std::shared_ptr<tl::Terrain> _terrain;
    };
} // namespace TerrainDemo
