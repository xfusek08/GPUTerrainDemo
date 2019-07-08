#pragma once

#include <memory>

#include <TerrainDemo/core/SDLRenderer.h>

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
        std::shared_ptr<core::SDLRenderer> _renderer = nullptr;
    };
}
