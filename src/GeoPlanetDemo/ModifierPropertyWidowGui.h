#pragma once

#include <string>
#include <vendor/imgui/imgui.h>

namespace gp
{
    namespace modifiers
    {
        class SurfaceModifier;
    }
}

namespace gpd
{
    class ModifierPropertyWidowGui
    {
    public:
        // properties
        ImVec2 position = { 0.f, 0.f };

        // methods
        ModifierPropertyWidowGui(std::string label, gp::modifiers::SurfaceModifier *modifier);

        inline bool getIsOpen() const { return isOpen; }
        inline float getHeight() const { return height; }
        inline std::string getLabel() const { return label; }
        inline gp::modifiers::SurfaceModifier *getModifier() const { return modifier; }
        inline bool isPlaced() const { return position.x != 0.f || position.y != 0.f;}

        void toggle();
        void draw();
    private:
        // properties
        std::string label = "";
        bool isOpen = false;
        float height = 0;
        gp::modifiers::SurfaceModifier *modifier;

        float textColumnWidth = 0.f;

        // methods
        void calcSizes();
    };
} // namespace gpd
