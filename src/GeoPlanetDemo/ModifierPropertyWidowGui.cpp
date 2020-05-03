
#include <GeoPlanetDemo/ModifierPropertyWidowGui.h>
#include <GeoPlanetLib/modifiers/modifiers.h>

using namespace std;
using namespace gpd;
using namespace gp::modifiers;

ModifierPropertyWidowGui::ModifierPropertyWidowGui(string label, SurfaceModifier *modifier) : label(label), modifier(modifier)
{
    calcSizes();
}

void ModifierPropertyWidowGui::toggle()
{
    if (isOpen) {
        isOpen = false;
        position = { 0.f, 0.f };
    } else {
        isOpen = true;
    }
}

void ModifierPropertyWidowGui::draw()
{
    if (!isOpen) {
        return;
    }

    ImGui::SetNextWindowPos(position);
    ImGui::SetNextWindowSize({ textColumnWidth + 150.f, 0 }, ImGuiCond_Always);
    ImGui::Begin(label.c_str(), &isOpen, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    if (isOpen) {
        ImGui::Columns(2, nullptr, false);
        ImGui::SetColumnWidth(0, textColumnWidth);
        for (auto pair : modifier->getVariables()) {
            auto variable = pair.second;;
            auto id = "##" + variable.getDescription();
            id.erase(std::remove_if(id.begin(), id.end(), ::isspace), id.end());
            ImGui::PushItemWidth(textColumnWidth);
            ImGui::Text((variable.getDescription() +":").c_str());
            ImGui::PopItemWidth();
            ImGui::NextColumn();
            ImGui::PushItemWidth(-1);
            switch (variable.getType())
            {
                case gp::modifiers::ModifierVariableType::Bool:
                    {
                        bool val = variable.getBool();
                        ImGui::Checkbox(id.c_str(), &val);
                        if (val != variable.getBool()) {
                            modifier->setBool(pair.first, val);
                        }
                    }
                    break;
                case gp::modifiers::ModifierVariableType::Integer:
                    {
                        int val = variable.getInt();
                        ImGui::InputInt(id.c_str(), &val);
                        if (variable.getInt() != val) {
                            modifier->setInt(pair.first, val);
                        }
                    }
                    break;
                case gp::modifiers::ModifierVariableType::Float:
                    {
                        float val = variable.getFloat();
                        ImGui::InputFloat(id.c_str(), &val, 0.1f);
                        if (variable.getFloat() != val) {
                            modifier->setFloat(pair.first, val);
                        }
                    }
                    break;
            }
            ImGui::PopItemWidth();
            ImGui::NextColumn();
            ImGui::Separator();
        }
    }
    ImGui::End();
}

// private
void ModifierPropertyWidowGui::calcSizes()
{
    int lines = 0;
    for (auto pair : modifier->getVariables()) {
        auto actSize = ImGui::CalcTextSize(pair.second.getDescription().c_str());
        if (actSize.x > textColumnWidth) {
            textColumnWidth = actSize.x;
        }
        lines++;
    }
    textColumnWidth += 20.f;
    height = 50 + lines * ImGui::GetFrameHeightWithSpacing();
}
