#pragma once

#include <glm/glm.hpp>

namespace TerrainDemo
{
    namespace core
    {
        class Entity
        {
        public:
            virtual std::vector<float>    getVerticies() const = 0;
            virtual std::vector<unsigned> getIndieces() const = 0;
            virtual glm::mat4             getTransformMatrix() const = 0;
        };
    } // core
} // namespace TerrainDemo
