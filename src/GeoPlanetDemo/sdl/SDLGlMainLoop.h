#pragma once

#include <memory>
#include <functional>
#include <vector>
#include <SDL.h>

#include <SDL2CPP/MainLoop.h>
#include <SDL2CPP/Window.h>

#include <GeoPlanetDemo/sdl/SDLPerformance.h>
#include <GeoPlanetDemo/sdl/SDLEventReceiverInterface.h>

namespace ge
{
    namespace gl
    {
        class Context;
    }
}

namespace  gpd
{
    namespace sdl
    {
        /**
         * TODO: make an implementation of MainLoopInterface with GPD_EVENT and EventReceiverInterface instead of SDL ones
         */
        class SDLGlMainLoop
        {
        public:
            SDLGlMainLoop(int width, int height);
            ~SDLGlMainLoop();

            inline std::shared_ptr<ge::gl::Context> getGlContext() const { return _gl; }
            inline std::shared_ptr<sdl2cpp::Window> getWindow()    const { return _window; }
            inline bool isInitialized() { return _initialized; }
            inline const SDLPerformance *getPerformance() { return &_performance; }

            virtual void init();
            virtual void run();
            virtual void addEventReceiver(std::shared_ptr<sdl::SDLEventReceiverInterface>);
            virtual void setEventHandler(std::function<bool(SDL_Event const&)> const& handler);
            virtual void setDrawCallback(std::function<void()> const& callback);

            inline void stop() { _mainLoop->stop(); }

        protected:
            // properties
            bool           _initialized  = false;
            int            _windowWidth  = 0;
            int            _windowHeight = 0;
            SDLPerformance _performance  = SDLPerformance();

            std::vector<std::shared_ptr<sdl::SDLEventReceiverInterface>> _eventReceivers;

            std::shared_ptr<sdl2cpp::Window>      _window = nullptr;
            std::shared_ptr<sdl2cpp::MainLoop>    _mainLoop = nullptr;
            std::function<bool(SDL_Event const&)> _eventHandler = nullptr;
            std::function<void()>                 _drawCallback = nullptr;
            std::shared_ptr<ge::gl::Context>      _gl = nullptr;

            // methods
            virtual bool update(SDL_Event const& event);
            virtual void draw();
        };

    } // namespace tdesdl
} // namespace  gpd
