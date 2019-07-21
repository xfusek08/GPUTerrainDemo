
#pragma once

#include <memory>

#include <TerrainDemo/core/Scene.h>

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
    namespace interfaces
    {
        class IVisualizationTechnique
        {
        public:
            virtual void draw() = 0;
            virtual void drawSetUp() = 0;
            virtual void setScene(std::shared_ptr<core::Scene> scene) = 0;

            std::shared_ptr<ge::gl::Context> gl;
            std::shared_ptr<ge::gl::Program> program;
        };
    }
}
