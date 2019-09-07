#pragma once

#include <TerrainDemo/tdsdl/SDLPerformance.h>
#include <TerrainDemo/tdsdl/SDLEventReceiverInterface.h>

#include <SDL2CPP/MainLoop.h>
#include <SDL2CPP/Window.h>

#include <memory>
#include <functional>
#include <vector>
#include <SDL.h>

namespace ge
{
    namespace gl
    {
        class Context;
    }
}

namespace sdl2cpp
{
    class Window;
    class MainLoop;
}

namespace TerrainDemo
{
    namespace tdsdl
    {
        /**
         * TODO: make an implementation of MainLoopInterface with TD_EVENT and EventReceiverInterface instead of SDL ones
         */
        class SDLGlMainLoop
        {
        public:
            SDLGlMainLoop(int width, int height);
            ~SDLGlMainLoop();

            inline std::shared_ptr<ge::gl::Context> getGlContext() { return _gl; }
            inline bool isInitialized() { return _initialized; }

            virtual void init();
            virtual void run();
            virtual void addEventReceiver(std::shared_ptr<tdsdl::SDLEventReceiverInterface>);
            virtual void setEventHandler(std::function<bool(SDL_Event const&)> const& handler);
            virtual void setDrawCallback(std::function<void()> const& callback);

        protected:
            virtual bool update(SDL_Event const& event);
            virtual void draw();

            bool _initialized           = false;
            int _windowWidth            = 0;
            int _windowHeight           = 0;
            SDLPerformance _performance = SDLPerformance();

            std::vector<std::shared_ptr<tdsdl::SDLEventReceiverInterface>> _eventReceivers;

            std::shared_ptr<sdl2cpp::Window>      _window = nullptr;
            std::shared_ptr<sdl2cpp::MainLoop>    _mainLoop = nullptr;
            std::function<bool(SDL_Event const&)> _eventHandler = nullptr;
            std::function<void()>                 _drawCallback = nullptr;
            std::shared_ptr<ge::gl::Context>      _gl = nullptr;
        };

    } // namespace tdesdl
} // namespace TerrainDemo
