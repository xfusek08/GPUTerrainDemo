
#pragma once

namespace TerrainDemo
{
	namespace core
	{
		class Camera;
	}

    namespace interfaces
    {
        class RendererInterface
        {
        public:
            virtual void updateScene() = 0;
            virtual void draw(std::shared_ptr<core::Camera>) const = 0;
        };
    }
}