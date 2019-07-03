#pragma once

#include <SDL.h>
#include <SDL2CPP/Window.h>
#include <SDL2CPP/MainLoop.h>

namespace TerrainDemo
{
    class SDLRenderer
    {
    public:
        SDLRenderer(
            std::shared_ptr<sdl2cpp::Window> window,
            std::shared_ptr<sdl2cpp::MainLoop> mainLoop
        );
        ~SDLRenderer();
        virtual void init();
        virtual void run();
        virtual bool update(SDL_Event const& event);
        virtual void draw();
    private:
        std::shared_ptr<sdl2cpp::Window>   _window = nullptr;
        std::shared_ptr<sdl2cpp::MainLoop> _mainLoop = nullptr;
    };
}