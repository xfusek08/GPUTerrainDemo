#pragma once

#include <glm/glm.hpp>

#include <GeoPlanetLib/Region.h>

#include <GeoPlanetDemo/vt/VTFactory.h>

namespace gpd
{
    namespace core
    {
        class Camera;
    }

    namespace entities {
        class PlanetEntity;
    }

    namespace vt
    {
        class PlanetVT : public VisualizationTechnique
        {
        public:
            // methods
            PlanetVT(VTType type, std::shared_ptr<ge::gl::Context> gl) : VisualizationTechnique(type, gl) {}

            inline GLenum getDrawMode() const override { return GL_TRIANGLES; }

            virtual void processScene(std::shared_ptr<core::Scene> scene) override;

            virtual glm::uvec4 regionToColor(std::shared_ptr<gp::Region> region);

        protected:
            // properties
            std::shared_ptr<entities::PlanetEntity> planet = nullptr;

            // methods
            virtual void initGlProgram() override;
            virtual std::shared_ptr<VAOContainer> processEntityToVaoContainer(std::shared_ptr<entities::Entity> entity) override;
            virtual void drawInternal(std::shared_ptr<core::Camera> camera) override;
        };
    } // namespace vt
} // namespace gpd

REGISTER_VT_TYPE(PlanetVT)
