#pragma once

#include <GeoPlanetDemo/Application.h>
#include <GeoPlanetDemo/sdl/SDLEventReceiverInterface.h>

#include <GeoPlanetDemo/vt/VTType.h>

namespace gpd
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

        void drawPrepare();
        void drawTearDown();

        vt::VTType intToVtType(int val)  const;
        int vtTypeToInt(vt::VTType val)  const;
    };
} // namespace gpd
