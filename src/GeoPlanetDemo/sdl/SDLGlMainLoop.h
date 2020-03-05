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

namespace gpd
{
    namespace sdl
    {
        /**
         * @todo description of class
         * @todo make an implementation of MainLoopInterface with GPD_EVENT and EventReceiverInterface instead of SDL ones
         * @todo get windows is unnecessary, use set new window size method intead
         * @todo width and height getters
         */
        class SDLGlMainLoop
        {
        public:
            // methods
            SDLGlMainLoop(int width, int height);
            ~SDLGlMainLoop();

            inline std::shared_ptr<ge::gl::Context> getGlContext() const { return gl; }
            inline std::shared_ptr<sdl2cpp::Window> getWindow()    const { return window; }
            inline bool isInitialized() { return initialized; }
            inline const SDLPerformance *getPerformance() { return &performance; }

            virtual void init();
            virtual void run();
            virtual void addEventReceiver(std::shared_ptr<sdl::SDLEventReceiverInterface>);
            virtual void setDrawCallback(std::function<void()> const& callback);

            inline void stop() { mainLoop->stop(); }

        protected:
            // properties
            bool           initialized  = false;
            int            windowWidth  = 0;
            int            windowHeight = 0;
            SDLPerformance performance  = SDLPerformance();

            std::vector<std::shared_ptr<sdl::SDLEventReceiverInterface>> eventReceivers;

            std::shared_ptr<sdl2cpp::Window>      window = nullptr;
            std::shared_ptr<sdl2cpp::MainLoop>    mainLoop = nullptr;
            std::function<bool(SDL_Event const&)> eventHandler = nullptr;
            std::function<void()>                 drawCallback = nullptr;
            std::shared_ptr<ge::gl::Context>      gl = nullptr;

            // methods
            virtual void setEventHandler(std::function<bool(SDL_Event const&)> const& handler);
            virtual bool update(SDL_Event const& event);
            virtual void draw();
        };

    } // namespace tdesdl
} // namespace gpd
