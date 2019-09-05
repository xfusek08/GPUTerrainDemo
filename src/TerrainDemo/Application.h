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
        Application();
        ~Application();

        virtual int init();
        virtual int run();
        virtual void draw();

    private:
        std::shared_ptr<tdsdl::SDLGlMainLoop> _mainLoop = nullptr; // TODO: use interfaces::MainLoopInterface to separate dependency on SDL
        std::shared_ptr<interfaces::RendererInterface> _renderer = nullptr;

        std::shared_ptr<core::Camera> _camera = nullptr;
        std::shared_ptr<core::Scene> _scene = nullptr;
    };
}
