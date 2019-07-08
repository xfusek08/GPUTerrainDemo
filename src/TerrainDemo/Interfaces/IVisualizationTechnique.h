
#pragma once

#include <memory>

#include <TerrainDemo/Interfaces/IScene.h>

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
    namespace Interfaces
    {
        class IVisualizationTechnique
        {
        public:
            virtual void draw() const = 0;
            virtual void drawSetUp() = 0;
            virtual void setScene(std::shared_ptr<IScene> scene) = 0;

            std::shared_ptr<ge::gl::Context> gl;
            std::shared_ptr<ge::gl::Program> program;
        };
    }
}
