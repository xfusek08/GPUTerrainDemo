
#include <geGL/geGL.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vendor/imgui/imgui.h>
#include <vendor/imgui/imgui_impl_sdl.h>
#include <vendor/imgui/imgui_impl_opengl3.h>

#include <GeoPlanetDemo/core/Camera.h>
#include <GeoPlanetDemo/core/Scene.h>
#include <GeoPlanetDemo/core/Utils.h>

#include <GeoPlanetDemo/sdl/SDLGlMainLoop.h>
#include <GeoPlanetDemo/sdl/SDLPerformance.h>

#include <GeoPlanetDemo/entities/PlanetEntity.h>

#include <GeoPlanetDemo/vt/planet/vts.h>

#include <GeoPlanetDemo/ApplicationGui.h>

using namespace std;
using namespace gpd;

ApplicationGui::ApplicationGui(Application* application) : application(application)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    auto gl = application->mainLoop->getGlContext();
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(application->mainLoop->getWindow()->getWindow(), nullptr);
    ImGui_ImplOpenGL3_Init("#version 430");
}

ApplicationGui::~ApplicationGui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

bool ApplicationGui::processSDLEvent(SDL_Event const& event)
{
    if (event.type == SDL_WINDOWEVENT) {
        switch (event.window.event)
        {
            case SDL_WINDOWEVENT_CLOSE:
                application->mainLoop->stop();
                break;
            case SDL_WINDOWEVENT_RESIZED:
                application->mainLoop->getWindow()->setSize(event.window.data1, event.window.data2);
                application->mainLoop->getGlContext()->glViewport(0, 0, event.window.data1, event.window.data2);
                application->camera->setViewSize(event.window.data1, event.window.data2);
                break;
        }
    }

    return ImGui_ImplSDL2_ProcessEvent(&event);
}

void ApplicationGui::onFrameUpdate()
{
}

void ApplicationGui::draw()
{
    drawPrepare();
    // create gui

    auto planetEntity = dynamic_pointer_cast<entities::PlanetEntity>(application->scene->getEntity("planet"));
    bool updateScene = false;

    // build main invisible window (left panel)
    ImGui::SetNextWindowPos({0,0});
    ImGui::SetNextWindowSize({300.0f, 0});
    ImGui::PushStyleColor(ImGuiCol_Text, {0.6f, 0.6f, 0.6f, 1});
    ImGui::PushStyleColor(ImGuiCol_WindowBg, {0, 0, 0, 0.9});

    ImGui::Begin("general", nullptr,
        ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoTitleBar
        | ImGuiWindowFlags_NoMove
        // | ImGuiWindowFlags_NoBackground
    );

    // FPS plotting
    {
        auto performance = application->mainLoop->getPerformance();
        char text[20];
        sprintf_s(text, 20, "FPS: %g", performance->getFrames());
        float fpsHistory[sdl::SDLPerformance::HISTORY_LEN];
        performance->getHistory(fpsHistory);
        ImGui::PlotLines(text, fpsHistory, sdl::SDLPerformance::HISTORY_LEN);
    }

    if (planetEntity != nullptr && ImGui::CollapsingHeader("Menu")) {
        ImGui::Text("Visualization technique:");
        {
            int vtTypeInt = vtTypeToInt(planetEntity->getVtType());
            ImGui::RadioButton("Default (F1)",              &vtTypeInt, vtTypeToInt(vt::types::PlanetVT));          // ImGui::SameLine();
            ImGui::RadioButton("Show Wireframe (F2)",       &vtTypeInt, vtTypeToInt(vt::types::PlanetWireFrameVT)); // ImGui::SameLine();
            ImGui::RadioButton("Show coordinate mask (F3)", &vtTypeInt, vtTypeToInt(vt::types::PlanetCubeMapVT));
            if (planetEntity->setVtType(intToVtType(vtTypeInt))) {
                updateScene = true;
                application->camera->setViewChanged();
            }

        }
        ImGui::Separator();

        ImGui::Text("Render options:");
        {
            bool showFaceColor = planetEntity->getShowFaceColor();
            ImGui::Checkbox("Show face color (f)", &showFaceColor);
            if (showFaceColor != planetEntity->getShowFaceColor()) {
                planetEntity->setShowFaceColor(showFaceColor);
                updateScene = true;
            }
        }
        {
            bool showCube = planetEntity->showCube;
            ImGui::Checkbox("Show as cube (c)", &showCube);
            if (showCube != planetEntity->showCube) {
                planetEntity->showCube = showCube;
                updateScene = true;
            }
        }
        {
            bool warpTexture = planetEntity->warpTexture;
            ImGui::Checkbox("warp texture (v)", &warpTexture);
            if (warpTexture != planetEntity->warpTexture) {
                planetEntity->warpTexture = warpTexture;
                updateScene = true;
            }
        }
        ImGui::Separator();

        ImGui::Text("Region generator setting:");
        {
            // resolution
            int resolution = planetEntity->getResolution();
            ImGui::PushItemWidth(100);
            ImGui::InputInt("Resolution (-o) (+p)", &resolution);
            if (resolution != planetEntity->getResolution()) {
                planetEntity->setResolution(resolution);
                updateScene = true;
            }
        }
        {
            // jitter
            float jitter = planetEntity->getJitter();
            // ImGui::PushItemWidth(100);
            ImGui::InputFloat("Jitter     (-j) (+k)", &jitter, 0.1f);
            if (jitter != planetEntity->getJitter()) {
                planetEntity->setJitter(jitter);
                updateScene = true;
            }
        }
        ImGui::Separator();

        // plate expand step
        {
            if (ImGui::Button("Step")) {
                planetEntity->stepPlateExpansion();
                updateScene = true;
            }
        }
        ImGui::Separator();

        ImGui::Text("Controls:");
        ImGui::Text("Zoom in:      (w)");
        ImGui::Text("Zoom out:     (s)");
        ImGui::Text("");
        ImGui::Text("Rotate up:    (up)");
        ImGui::Text("Rotate down:  (down)");
        ImGui::Text("Rotate left:  (left)");
        ImGui::Text("Rotate right: (right)");

        if (updateScene) {
            application->renderer->updateScene();
        }
    }

    ImGui::End();
    ImGui::PopStyleColor();
    ImGui::PopStyleColor();
    drawTearDown();
}

// private supportive functions

void ApplicationGui::drawPrepare()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(application->mainLoop->getWindow()->getWindow());
    ImGui::NewFrame();
}

void ApplicationGui::drawTearDown()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

vt::VTType ApplicationGui::intToVtType(int val) const
{
    auto list = vt::VTFactory::list();
    if (val < 0 || val > list.size()) {
        return vt::types::UndefinedVT;
    }
    return list[val];
}

int ApplicationGui::vtTypeToInt(vt::VTType val) const
{
    size_t index = 0;
    for (auto type : vt::VTFactory::list()) {
        if (type == val) {
            return index;
        }
        ++index;
    }
    GPD_ASSERT(false, "ApplicationGui::vtTypeToInt(" << val << "): not found.");
    return -1;
}
