#pragma once

#include <memory>
#include <vector>
#include <geGL/Generated/OpenGLTypes.h>

namespace ge
{
    namespace gl
    {
		class VertexArray;
		class Buffer;
		class Texture;
		class Context;
    }
}

namespace TerrainDemo
{
    namespace vt
    {
        class VAOContainer {
        public:
            std::shared_ptr<ge::gl::VertexArray> vao;
			GLsizei indexSize;

            VAOContainer(std::shared_ptr<ge::gl::Context> gl);

            void bind();
            void unbind();

            void addTexture(std::shared_ptr<ge::gl::Texture> texture);

			template<typename T> std::shared_ptr<ge::gl::Buffer> newBuffer(std::vector<T> values)
			{
				auto buffer = std::make_shared<ge::gl::Buffer>(values.size() * sizeof(T), values.data());
				_bufferContainer.push_back(buffer);
				return buffer;
			}

		protected:
            std::vector<std::shared_ptr<ge::gl::Buffer>> _bufferContainer;
            std::vector<std::shared_ptr<ge::gl::Texture>> _textureContainer;
		};
    } // namespace vt
} // namespace TerrainDemo