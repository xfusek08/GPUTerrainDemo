#pragma once

#include <TerrainDemo/entities/Entity.h>

namespace TerrainDemo
{
    namespace entities
    {
        class AxisEntity : public entities::Entity
        {
        public:
            AxisEntity(vt::VTType vtType);

            void loadToVaoElement(std::shared_ptr<vt::VAOContainer> vaoElem) override;

			inline std::vector<float> getColors() const { return _colors; }

        protected:
			std::vector<float> _colors = { 0.f };
        };
    } // namespace entities
} // namespace TerrainDemo
