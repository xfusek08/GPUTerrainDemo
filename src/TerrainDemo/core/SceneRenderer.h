#pragma once

#include <memory>
#include <unordered_map>

#include <TerrainDemo/interfaces/RendererInterface.h>
#include <TerrainDemo/vt/types.h>

namespace ge
{
	namespace gl
	{
		class Context;
	}
}

namespace TerrainDemo
{
	namespace vt
	{
		class BaseVisualizationTechnique;
	}

    namespace core
    {
		class Camera;
		class Scene;

        class SceneRenderer : public interfaces::RendererInterface
        {
        public:
            SceneRenderer(std::shared_ptr<ge::gl::Context> context, std::shared_ptr<Scene> scene);

            virtual void updateScene() override;
            virtual void draw(std::shared_ptr<Camera>) const override;

        protected:
            std::shared_ptr<Scene> _scene;
			std::shared_ptr<ge::gl::Context> _gl;
			std::unordered_map<vt::VTType, std::shared_ptr<vt::BaseVisualizationTechnique>> _vts;
        };
    } // core
} // namespace TerrainDemo
