#pragma once

#include <memory>
#include <vector>

#include <TerrainDemo/core/Entity.h>

namespace TerrainDemo
{
    namespace core
    {
        class Scene
        {
        public:
            Scene() {}
            inline std::vector<std::shared_ptr<Entity>> getEntities() const { return _entities; }
            inline void addEntity(std::shared_ptr<Entity> entity) { _entities.push_back(entity); }
        protected:
            std::vector<std::shared_ptr<Entity>> _entities;
        };
    } // core
} // namespace TerrainDemo
