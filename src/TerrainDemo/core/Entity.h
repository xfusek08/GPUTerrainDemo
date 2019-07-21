#pragma once

#include <memory>

#include <geGL/geGL.h>
#include <glm/glm.hpp>


namespace TerrainDemo
{
    namespace core
    {
        class Entity
        {
        public:
            Entity();

            GLenum drawMode = GL_TRIANGLES;
            GLenum drawType = GL_UNSIGNED_INT;

            std::shared_ptr<ge::gl::VertexArray> vao;

            void initVao(std::shared_ptr<ge::gl::Context> gl);

            inline std::vector<float>    getVerticies()         { return _verticies; }
            inline std::vector<unsigned> getIndieces()          { return _indicies; }
            inline glm::mat4             getTransformMatrix()   { return _transform; }
        protected:
            virtual void defineVaoAttributes();

            template<typename T> std::shared_ptr<ge::gl::Buffer> newVaoBuffer(std::vector<T> values)
            {
                auto buffer = std::make_shared<ge::gl::Buffer>(values.size() * sizeof(T), values.data());
                _bufferContainer.push_back(buffer);
                return buffer;
            }

            std::vector<float>      _verticies;
            std::vector<unsigned>   _indicies;
            glm::mat4               _transform = glm::mat4(1);

            std::vector<std::shared_ptr<ge::gl::Buffer>> _bufferContainer;
        };
    } // core
} // namespace TerrainDemo
