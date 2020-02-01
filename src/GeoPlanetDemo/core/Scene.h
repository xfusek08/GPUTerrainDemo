#pragma once

#include <memory>
#include <map>
#include <vector>
#include <string>

#include <GeoPlanetDemo/entities/Entity.h>

namespace  gpd
{
    namespace core
    {
        class Scene
        {
        public:
            Scene() {}
            std::vector<std::shared_ptr<entities::Entity>> getEntities() const;

            inline void addEntity(std::string id, std::shared_ptr<entities::Entity> entity) { _entities[id] = entity; }
            inline std::shared_ptr<entities::Entity> getEntity(std::string id) { return _entities[id]; }

        protected:
            std::map<std::string, std::shared_ptr<entities::Entity>> _entities;
        };
    } // core
} // namespace  gpd
