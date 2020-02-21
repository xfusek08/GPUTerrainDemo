#pragma once

#include <GeoPlanetDemo/Application.h>
#include <GeoPlanetDemo/sdl/SDLEventReceiverInterface.h>

namespace gpd
{
    class ApplicationEventReceiver : public sdl::SDLEventReceiverInterface
    {
    public:
        ApplicationEventReceiver(Application* application): application(application) {}
        bool processSDLEvent(SDL_Event const&) override;
        void onFrameUpdate() override;

    private:
        Application* application;
    };
} // namespace gpd