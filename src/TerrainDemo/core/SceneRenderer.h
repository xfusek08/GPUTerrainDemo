#pragma once

#include <memory>

#include <TerrainDemo/core/Scene.h>
#include <TerrainDemo/interfaces/RendererInterface.h>

namespace ge
{
	namespace gl
	{
		class Context;
	}
}

namespace TerrainDemo
{
    namespace core
    {
		class Camera;

        class SceneRenderer : public interfaces::RendererInterface
        {
        public:
            SceneRenderer(std::shared_ptr<ge::gl::Context> context, std::shared_ptr<Scene> scene);

            virtual void updateScene() override;
            virtual void draw(std::shared_ptr<Camera>) const override;

        protected:
            std::shared_ptr<Scene> _scene;
			std::shared_ptr<ge::gl::Context> _gl;
        };
    } // core
} // namespace TerrainDemo
