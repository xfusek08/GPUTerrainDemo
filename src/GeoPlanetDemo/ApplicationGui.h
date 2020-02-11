#pragma once

#include <GeoPlanetDemo/Application.h>
#include <GeoPlanetDemo/sdl/SDLEventReceiverInterface.h>

namespace  gpd
{
    class ApplicationGui : public sdl::SDLEventReceiverInterface
    {
    public:
        ApplicationGui(Application* application);
        ~ApplicationGui();
        bool processSDLEvent(SDL_Event const&) override;
        void onFrameUpdate() override;
        void draw();

    private:
		Application* application;
    };
} // namespace  gpd