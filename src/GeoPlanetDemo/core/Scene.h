#pragma once

#include <memory>
#include <map>
#include <vector>
#include <string>

#include <GeoPlanetDemo/entities/Entity.h>

namespace gpd
{
    namespace core
    {
        class Scene
        {
        public:
            Scene() {}
            std::vector<std::shared_ptr<entities::Entity>> getEntities() const;

            inline void addEntity(std::string id, std::shared_ptr<entities::Entity> entity) { entities[id] = entity; }
            inline std::shared_ptr<entities::Entity> getEntity(std::string id) { 
                auto it = entities.find(id); 
                return (it != entities.end()) ? it->second : nullptr;
            }

        protected:
            std::map<std::string, std::shared_ptr<entities::Entity>> entities;
        };
    } // core
} // namespace gpd
