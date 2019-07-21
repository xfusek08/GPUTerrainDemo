#pragma once

/**
 * @Brief       Class wrapping main SDL loop for visualization technique and rendering a scene
 * @Author      Petr Fusek
 * @Project     TerrainLibDemo
 * @File        SDLRenderer.h
 */

#include <vector>

#include <SDL.h>
#include <SDL2CPP/Window.h>
#include <SDL2CPP/MainLoop.h>

#include <TerrainDemo/interfaces/ISDLEventReceiver.h>
#include <TerrainDemo/interfaces/IVisualizationTechnique.h>

#include <TerrainDemo/tdsdl/SDLPerformance.h>

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
    namespace tdsdl
    {
        class SDLRenderer
        {
        public:
            SDLRenderer(
                std::shared_ptr<sdl2cpp::Window> window,
                std::shared_ptr<sdl2cpp::MainLoop> mainLoop,
                std::shared_ptr<interfaces::IVisualizationTechnique> vt
            );
            ~SDLRenderer();

            virtual void init();
            virtual void run();
            virtual void addEventReceiver(std::shared_ptr<interfaces::ISDLEventReceiver>);
            virtual void setVT(std::shared_ptr<interfaces::IVisualizationTechnique> vt);

        protected:
            virtual bool update(SDL_Event const& event);
            virtual void draw();

            bool _initialized = false;
            SDLPerformance _performance = SDLPerformance();

            std::vector<std::shared_ptr<interfaces::ISDLEventReceiver>> _eventReceivers;

            std::shared_ptr<sdl2cpp::Window> _window = nullptr;
            std::shared_ptr<sdl2cpp::MainLoop> _mainLoop = nullptr;
            std::shared_ptr<interfaces::IVisualizationTechnique> _vt = nullptr;
            std::shared_ptr<ge::gl::Context> _gl;
        };

    } // namespace tdesdl
} // namespace TerrainDemo
