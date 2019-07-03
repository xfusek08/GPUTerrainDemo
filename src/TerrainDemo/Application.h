
#pragma once

#include <memory>

#include <TerrainDemo/SDLRenderer.h>

namespace TerrainDemo
{
    class Application
    {
    public:
        Application();
        ~Application();

        virtual int init();
        virtual int run();
    private:
        std::shared_ptr<TerrainDemo::SDLRenderer> _renderer = nullptr;
    };
}
