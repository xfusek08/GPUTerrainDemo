#pragma once

#include <vector>

namespace gpd
{
    namespace scene
    {
        class Entity
        {
        public:
            Entity() {}
            ~Entity() {}

            virtual const std::vector<float>    getVerticies() const;
            virtual const std::vector<unsigned> getIndieces()  const;
            virtual const std::vector<float>    getColors()    const;
        };
    } // namespace scene
} // namespace gpd
