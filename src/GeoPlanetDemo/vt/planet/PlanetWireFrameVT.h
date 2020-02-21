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
            // properties
            std::shared_ptr<ge::gl::Program> program_faces;
            std::shared_ptr<ge::gl::Program> program_lines;

            // methods
            virtual void initGlProgram() override;
            virtual void draw(std::shared_ptr<core::Camera> camera) override;
            virtual std::shared_ptr<VAOContainer> processEntityToVaoContainer(std::shared_ptr<entities::Entity> entity) override;
        };
    } // namespace vt
} // namespace gpd

REGISTER_VT_TYPE(PlanetWireFrameVT)
