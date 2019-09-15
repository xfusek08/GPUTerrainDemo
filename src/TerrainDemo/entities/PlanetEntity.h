#pragma once

#include <TerrainDemo/entities/Entity.h>

namespace TerrainDemo
{
    namespace entities
    {
        class PlanetEntity : public entities::Entity
        {
        public:
            PlanetEntity(vt::VTType vtType);

            void loadToVaoElement(std::shared_ptr<vt::VAOContainer> vaoElem) override;

        protected:
			std::vector<float> _colors = { 0.f };
        };
    } // namespace entities
} // namespace TerrainDemo
