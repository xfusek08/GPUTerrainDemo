#pragma once

#include <TerrainDemo/Application.h>
#include <TerrainDemo/tdsdl/SDLEventReceiverInterface.h>

namespace TerrainDemo
{
    class ApplicationEventReciever : public tdsdl::SDLEventReceiverInterface
    {
    public:
        ApplicationEventReciever(Application* application): _application(application) {}
        bool processSDLEvent(SDL_Event const&) override;
        void onFrameUpdate() override;

    private:
		Application* _application;
    };
} // namespace TerrainDemo