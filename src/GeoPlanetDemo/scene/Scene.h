#pragma once

#include <memory>
#include <string>
#include <vector>
#include <map>

#include <GeoPlanetDemo/vt/VTType.h>

#include <GeoPlanetDemo/scene/Entity.h>

namespace gpd
{
    namespace scene
    {
        struct SceneElement
        {
            vt::VTType vtType = vt::types::UndefinedVT;
            std::shared_ptr<Entity> entity = nullptr;

            bool isValid()
            {
                return vtType != vt::types::UndefinedVT && entity != nullptr;
            }
        };

        class Scene
        {
        public:
            // methods
            Scene() {}
            const std::vector<SceneElement> getElements() const;

            inline void setElement(std::string name, SceneElement element) { elements[name] = element; }

            SceneElement getElement(std::string name);

        protected:
            // properties
            std::map<std::string, SceneElement> elements;
        };
    } // namespace scene
} // namespace gpd
