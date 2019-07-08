#pragma once

/**
 * @Brief       Class wrapping main SDL loop for visualization technique and rendering a scene
 * @Author      Petr Fusek
 * @Project     GPUTerrainDemo
 * @File        SDLRenderer.h
 */

#include <SDL.h>
#include <SDL2CPP/Window.h>
#include <SDL2CPP/MainLoop.h>

#include <TerrainDemo/core/SDLControls.h>

#include <TerrainDemo/Interfaces/IControls.h>
#include <TerrainDemo/Interfaces/IScene.h>
#include <TerrainDemo/Interfaces/IVisualizationTechnique.h>

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
        class SDLRenderer
        {
        public:
            SDLRenderer(
                std::shared_ptr<sdl2cpp::Window> window,
                std::shared_ptr<sdl2cpp::MainLoop> mainLoop,
                std::shared_ptr<Interfaces::IVisualizationTechnique> vt
            );
            ~SDLRenderer();

            virtual void init();
            virtual void run();
            virtual void setControls(std::shared_ptr<SDLControls> controls); // for SDL renderer we need SDLControls
            virtual void setVT      (std::shared_ptr<Interfaces::IVisualizationTechnique> vt);
            virtual void setScene   (std::shared_ptr<Interfaces::IScene> scene);
        protected:
            virtual bool update(SDL_Event const& event);
            virtual void draw();

            std::shared_ptr<sdl2cpp::Window> _window = nullptr;
            std::shared_ptr<sdl2cpp::MainLoop> _mainLoop = nullptr;

            std::shared_ptr<SDLControls> _controls = nullptr;
            std::shared_ptr<Interfaces::IVisualizationTechnique> _vt = nullptr;
            std::shared_ptr<Interfaces::IScene> _scene = nullptr;

            std::shared_ptr<ge::gl::Context> _gl;
            std::shared_ptr<ge::gl::Program> _program;

        private:
            bool _initialized = false;
        };

    } // namespace core
} // namespace TerrainDemo
