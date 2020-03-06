#pragma once

#include <memory>
#include <unordered_map>

#include <GeoPlanetDemo/interfaces/RendererInterface.h>
#include <GeoPlanetDemo/vt/VTType.h>

namespace ge
{
    namespace gl
    {
        class Context;
    }
}

namespace gpd
{
    namespace scene
    {
        class Scene;
    }

    namespace vt
    {
        class VisualizationTechnique;
    }

    namespace core
    {
        class Camera;

        class SceneRenderer : public interfaces::RendererInterface
        {
        public:
            SceneRenderer(std::shared_ptr<ge::gl::Context> context, std::shared_ptr<scene::Scene> scene);

            virtual void updateScene() override;
            virtual void draw(std::shared_ptr<core::Camera>) const override;

        protected:
            std::shared_ptr<scene::Scene> scene;
            std::shared_ptr<ge::gl::Context> gl;
            std::unordered_map<vt::VTType, std::shared_ptr<vt::VisualizationTechnique>> vts;
        };
    } // core
} // namespace gpd
