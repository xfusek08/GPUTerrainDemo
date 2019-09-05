
#pragma once

#include <memory>

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
	}

    namespace vt
    {
        class BaseVisualizationTechnique
        {
        public:
            BaseVisualizationTechnique(std::shared_ptr<ge::gl::Context> gl);

            inline bool isSetUp() const { return _isSetUp; }
            inline std::shared_ptr<ge::gl::Context> getGlContext() const { return _gl; }
            inline std::shared_ptr<ge::gl::Program> getGlProgram() const { return _program; }

            virtual void drawSetUp();
            virtual void draw(std::shared_ptr<core::Camera> camera);

        protected:
            bool _isSetUp = false;
            std::shared_ptr<ge::gl::Context> _gl;
            std::shared_ptr<ge::gl::Program> _program;

            virtual void initGl();
            virtual void initGlProgram();

            virtual void beforeDraw(std::shared_ptr<core::Camera> camera);
            virtual void drawInternal(std::shared_ptr<core::Camera> camera);
            virtual void afterDraw(std::shared_ptr<core::Camera> camera);
        };
    } // namespace vt
} // namespace TerrainDemo