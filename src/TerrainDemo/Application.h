
#pragma once

#include <geAd/SDLWindow/SDLWindow.h>
#include <geAd/SDLWindow/SDLMainLoop.h>

#include <memory>

namespace TerrainDemo
{
    class Application
    {
    public:
        Application();
        ~Application();

        virtual int init();
        virtual int run();

    protected:
        virtual bool update(SDL_Event const& event);
        virtual void draw();
    private:
        std::shared_ptr<ge::ad::SDLMainLoop> _mainLoop = nullptr;
        std::shared_ptr<ge::ad::SDLWindow>   _window = nullptr;
    };
}
