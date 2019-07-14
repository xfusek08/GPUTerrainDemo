#pragma once

#include <memory>

#include <TerrainDemo/tdsdl/SDLRenderer.h>

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
        std::shared_ptr<tdsdl::SDLRenderer> _renderer = nullptr;
    };
}
