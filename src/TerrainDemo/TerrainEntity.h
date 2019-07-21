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
        virtual std::vector<float> getVerticies() const override;
        virtual std::vector<unsigned> getIndieces() const override;
        virtual glm::mat4 getTransformMatrix() const override;
    protected:
        std::shared_ptr<tl::Terrain> _terrain;
    };
} // namespace TerrainDemo
