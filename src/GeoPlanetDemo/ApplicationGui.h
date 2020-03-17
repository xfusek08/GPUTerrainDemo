#pragma once

#include <GeoPlanetDemo/Application.h>
#include <GeoPlanetDemo/sdl/SDLEventReceiverInterface.h>

#include <GeoPlanetDemo/vt/VTType.h>

namespace gp
{
    struct ModifierListItem;
}

namespace gpd
{
    class ApplicationGui : public sdl::SDLEventReceiverInterface
    {
    public:
        // methods
        ApplicationGui(Application* application);
        ~ApplicationGui();

        bool processSDLEvent(SDL_Event const&) override;
        void onFrameUpdate() override;
        void draw();
        bool renderModifierItem(gp::ModifierListItem modifier, std::shared_ptr<gp::SurfaceGenerator> generator);

    private:
        // properties
        Application* application;
        std::unordered_map<std::string, bool> openWindows;

        // methods
        void drawPrepare();
        void drawTearDown();

        vt::VTType intToVtType(int val)  const;
        int vtTypeToInt(vt::VTType val)  const;

        // general api simplifications
        void checkbox(const char* label, bool val, std::function<void(bool)> onChangeCallback);
        void window(std::string label, std::function<void(void)> drawCallback);

        // specific gui parts
        void drawGeneratorGui(std::shared_ptr<gp::SurfaceGenerator> generator);
        void showModifierEditorWindow(std::string label, std::shared_ptr<gp::SurfaceModifier> modifier);
    };
} // namespace gpd
