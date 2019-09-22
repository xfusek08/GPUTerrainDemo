#pragma once

#include <memory>
#include <unordered_map>
#include <TerrainDemo/vt/types.h>
#include <geGL/Generated/OpenGLTypes.h>
#include <geGL/Generated/OpenGLConstants.h>

namespace ge
{
    namespace gl
    {
        class Context;
        class Program;
    }
}

namespace TerrainDemo
{
	namespace core
	{
		class Camera;
		class Scene;
	}

	namespace entities {
		class Entity;
	}

    namespace vt
    {
        class VAOContainer;

        class BaseVisualizationTechnique
        {
        public:
            BaseVisualizationTechnique(std::shared_ptr<ge::gl::Context> gl);

			virtual inline VTType getType() const { return VTType::BaseVisualizationTechnique; }
			virtual inline GLenum getDrawMode() const { return GL_TRIANGLES; }

			inline bool isInitialized() const { return _isInitialized; }
			inline std::shared_ptr<ge::gl::Context> getGlContext() const { return _gl; }
            inline std::shared_ptr<ge::gl::Program> getGlProgram() const { return _program; }

			virtual void init();
			virtual void drawSetUp();
            virtual void draw(std::shared_ptr<core::Camera> camera);
			virtual void clean();
			virtual void processScene(std::shared_ptr<core::Scene> scene);

        protected:
            bool _isInitialized = false;
			std::shared_ptr<ge::gl::Context> _gl;
            std::shared_ptr<ge::gl::Program> _program;
			std::unordered_map<entities::Entity*, std::shared_ptr<VAOContainer>> _vaoContainerMap;

            virtual void initGl();
            virtual void initGlProgram();

			virtual std::shared_ptr<VAOContainer> processEntityToVaoContainer(std::shared_ptr<entities::Entity> entity);

			virtual void beforeDraw(std::shared_ptr<core::Camera> camera);
            virtual void drawInternal(std::shared_ptr<core::Camera> camera);
            virtual void afterDraw(std::shared_ptr<core::Camera> camera);
        };
    } // namespace vt
} // namespace TerrainDemo