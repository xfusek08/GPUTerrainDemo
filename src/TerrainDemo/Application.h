#pragma once

#include <memory>

#include <TerrainDemo/interfaces/RendererInterface.h>

namespace TerrainDemo
{
	namespace core
	{
		class Scene;
		class Camera;
	}
	namespace tdsdl
	{
		class SDLGlMainLoop;
	}

    class Application
    {
    public:
		const int WINDOW_WIDTH  = 1920;
		const int WINDOW_HEIGHT = 1080;

		std::shared_ptr<tdsdl::SDLGlMainLoop>           mainLoop = nullptr;
		std::shared_ptr<interfaces::RendererInterface>  renderer = nullptr;
		std::shared_ptr<core::Camera>                   camera = nullptr;
		std::shared_ptr<core::Scene>                    scene = nullptr;

		Application();
        ~Application();

        virtual int init();
        virtual int run();
        virtual void draw();

    };
}
