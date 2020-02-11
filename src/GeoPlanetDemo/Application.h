#pragma once

#include <memory>

#include <GeoPlanetDemo/interfaces/RendererInterface.h>

namespace  gpd
{
	namespace core
	{
		class Scene;
		class Camera;
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
		const int WINDOW_WIDTH  = 1280;
		const int WINDOW_HEIGHT = 720;

        // properties
		std::shared_ptr<sdl::SDLGlMainLoop>             mainLoop = nullptr;
		std::shared_ptr<interfaces::RendererInterface>  renderer = nullptr;
		std::shared_ptr<core::Camera>                   camera = nullptr;
		std::shared_ptr<core::Scene>                    scene = nullptr;
        std::shared_ptr<ApplicationGui>                 gui = nullptr;

        // methods
		Application() {}
        ~Application() {}

        virtual int init();
        virtual int run();
        virtual void draw();
    };
}
