#pragma once

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include <TerrainDemo/vt/types.h>

namespace TerrainDemo
{
    namespace core
    {
        class Entity
        {
        public:
            Entity(vt::VTType vtType = vt::VTType::BaseVisualizationTechnique);
            Entity(
                vt::VTType vtType,
                std::vector<float>    verticies,
                std::vector<unsigned> indicies
            );
			virtual ~Entity() {}

			inline vt::VTType			 getVtType()			const { return _vtType; }
			inline std::vector<float>    getVerticies()         const { return _verticies; }
            inline std::vector<unsigned> getIndieces()          const { return _indicies; }
            inline glm::mat4             getTransformMatrix()   const { return _transform; }
        protected:
            std::vector<float>      _verticies;
            std::vector<unsigned>   _indicies;
            glm::mat4               _transform  = glm::mat4(1);
            vt::VTType              _vtType;

        };
    } // core
} // namespace TerrainDemo

