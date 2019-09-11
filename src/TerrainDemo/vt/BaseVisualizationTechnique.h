#pragma once

#include <memory>
#include <unordered_map>
#include <TerrainDemo/vt/types.h>

#include <geGL/Generated/OpenGLTypes.h>

namespace ge
{
    namespace gl
    {
        class Context;
        class Program;
		class VertexArray;
		class Buffer;
    }
}

namespace TerrainDemo
{
	namespace core
	{
		class Camera;
		class Scene;
        class Entity;
	}

    namespace vt
    {
		struct VAOContainerElement {
			std::shared_ptr<ge::gl::VertexArray> vao;
			GLsizei indexSize;
		};

        class BaseVisualizationTechnique
        {
        public:
            BaseVisualizationTechnique(std::shared_ptr<ge::gl::Context> gl);

			virtual inline VTType getType() const { return VTType::BaseVisualizationTechnique; }

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
			std::vector<std::shared_ptr<ge::gl::Buffer>> _bufferContainer;

			// _vaoContainer = { entity: (vao, indexSize), ... }
			std::unordered_map<entities::Entity*, VAOContainerElement> _vaoContainer;

            virtual void initGl();
            virtual void initGlProgram();

			virtual VAOContainerElement processEntityToVao(std::shared_ptr<entities::Entity> entity);

			virtual void beforeDraw(std::shared_ptr<core::Camera> camera);
            virtual void drawInternal(std::shared_ptr<core::Camera> camera);
            virtual void afterDraw(std::shared_ptr<core::Camera> camera);

			template<typename T> std::shared_ptr<ge::gl::Buffer> newVaoBuffer(std::vector<T> values)
            {
                auto buffer = std::make_shared<ge::gl::Buffer>(values.size() * sizeof(T), values.data());
                _bufferContainer.push_back(buffer);
                return buffer;
            }
        };
    } // namespace vt
} // namespace TerrainDemo