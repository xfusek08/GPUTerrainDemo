#pragma once

#include <memory>
#include <unordered_map>

#include <geGL/Generated/OpenGLTypes.h>
#include <geGL/Generated/OpenGLConstants.h>

#include <GeoPlanetDemo/vt/VTType.h>

namespace ge
{
    namespace gl
    {
        class Context;
        class Program;
    }
}

namespace gpd
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

        class VisualizationTechnique
        {
        public:
            VisualizationTechnique(VTType type, std::shared_ptr<ge::gl::Context> gl) : type(type), gl(gl) {}

            virtual inline GLenum getDrawMode() const { return GL_TRIANGLES; }

            inline std::shared_ptr<ge::gl::Context> getGlContext()  const { return gl; }
            inline std::shared_ptr<ge::gl::Program> getGlProgram()  const { return program; }
            inline bool   getIsInitialized() const { return isInitialized; }
            inline VTType getType()          const { return type; }

            virtual void init();
            virtual void clean();
            virtual void drawSetUp();
            virtual void draw(std::shared_ptr<core::Camera> camera);
            virtual void processScene(std::shared_ptr<core::Scene> scene);

        protected:
            // properties
            VTType type = types::UndefinedVT;
            bool isInitialized = false;
            std::shared_ptr<ge::gl::Context> gl;
            std::shared_ptr<ge::gl::Program> program;
            std::unordered_map<entities::Entity*, std::shared_ptr<VAOContainer>> vaoContainerMap;

            // methods
            virtual void initGl();
            virtual void initGlProgram();

            virtual void beforeDraw(std::shared_ptr<core::Camera> camera);
            virtual void drawInternal(std::shared_ptr<core::Camera> camera);
            virtual void afterDraw(std::shared_ptr<core::Camera> camera);

            virtual std::shared_ptr<VAOContainer> processEntityToVaoContainer(std::shared_ptr<entities::Entity> entity);
        };
    } // namespace vt
} // namespace gpd
