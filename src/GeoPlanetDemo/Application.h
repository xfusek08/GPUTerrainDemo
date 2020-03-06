#pragma once

#include <memory>

#include <GeoPlanetDemo/interfaces/RendererInterface.h>

namespace gpd
{
    namespace core
    {
        class Camera;
    }

    namespace scene
    {
        class Scene;
    }

    namespace sdl
    {
        class SDLGlMainLoop;
    }

    class ApplicationGui;

    class Application
    {
    public:
        // constants
        static const int DEFAULT_WINDOW_WIDTH  = 1280;
        static const int DEFAULT_WINDOW_HEIGHT = 720;

        // properties
        std::shared_ptr<sdl::SDLGlMainLoop>            mainLoop = nullptr;
        std::shared_ptr<interfaces::RendererInterface> renderer = nullptr;
        std::shared_ptr<core::Camera>                  camera = nullptr;
        std::shared_ptr<scene::Scene>                  scene = nullptr;
        std::shared_ptr<ApplicationGui>                gui = nullptr;

        // methods
        Application() {}
        ~Application() {}

        virtual int init();
        virtual int run();
        virtual void draw();
    };
}
