#pragma once

#include <GeoPlanetDemo/vt/planet/PlanetVT.h>

namespace gpd
{
    namespace core
    {
        class Camera;
    }

    namespace vt
    {
        class PlanetWireFrameVT : public PlanetVT
        {
        public:
            // methods
            PlanetWireFrameVT(VTType type, std::shared_ptr<ge::gl::Context> gl) : PlanetVT(type, gl) {}

            virtual glm::uvec4 regionToColor(std::shared_ptr<gp::Region> region) override { return glm::uvec4(255, 255, 255, 0); }

        protected:
            // methods
            virtual void initGl() override;
            virtual void initGlProgram() override;
            virtual std::shared_ptr<VAOContainer> processEntityToVaoContainer(std::shared_ptr<scene::Entity> entity) override;
        };
    } // namespace vt
} // namespace gpd

REGISTER_VT_TYPE(PlanetWireFrameVT)
