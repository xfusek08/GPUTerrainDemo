
#include <geGL/geGL.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vendor/imgui/imgui.h>
#include <vendor/imgui/imgui_impl_sdl.h>
#include <vendor/imgui/imgui_impl_opengl3.h>

#include <GeoPlanetDemo/core/Camera.h>
#include <GeoPlanetDemo/core/Utils.h>

#include <GeoPlanetDemo/sdl/SDLGlMainLoop.h>
#include <GeoPlanetDemo/sdl/SDLPerformance.h>

#include <GeoPlanetDemo/scene/Scene.h>
#include <GeoPlanetDemo/scene/entities/PlanetEntity.h>

#include <GeoPlanetDemo/vt/planet/vts.h>

#include <GeoPlanetDemo/ApplicationGui.h>

using namespace std;
using namespace gpd;
using namespace gpd::scene::entities;

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

    auto planetSceneElement = application->scene->getElement("planet");
    auto planetEntity = dynamic_pointer_cast<PlanetEntity>(planetSceneElement.entity);
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
        ImGui::Text("Base layer visualization technique:");
        {
            int vtTypeInt = vtTypeToInt(planetSceneElement.vtType);
            ImGui::RadioButton("Show elevation       (F1)", &vtTypeInt, vtTypeToInt(vt::types::PlanetElevationVT));
            ImGui::RadioButton("Show tectonic plates (F2)", &vtTypeInt, vtTypeToInt(vt::types::PlanetPlatesVT));
            ImGui::RadioButton("Show coordinate mask (F3)", &vtTypeInt, vtTypeToInt(vt::types::PlanetCubeMapVT));
            ImGui::RadioButton("Show face colors     (F4)", &vtTypeInt, vtTypeToInt(vt::types::PlanetFaceColorVT));
            if (planetSceneElement.vtType != intToVtType(vtTypeInt)) {
                planetSceneElement.vtType = intToVtType(vtTypeInt);
                application->scene->setElement("planet", planetSceneElement);
                application->camera->setViewChanged();
                updateScene = true;
            }
        }
        ImGui::Separator();

        ImGui::Text("Surface data visualization:");
        {
            auto plateDataElement = application->scene->getElement("planet_data");
            int vtTypeInt = vtTypeToInt(plateDataElement.vtType);
            ImGui::RadioButton("Disabled       (1)", &vtTypeInt, vtTypeToInt(vt::types::UndefinedVT));
            ImGui::RadioButton("Plate movement (2)", &vtTypeInt, vtTypeToInt(vt::types::PlanetVectorsVT));
            if (plateDataElement.vtType != intToVtType(vtTypeInt)) {
                plateDataElement.vtType = intToVtType(vtTypeInt);
                application->scene->setElement("planet_data", plateDataElement);
                application->camera->setViewChanged();
                updateScene = true;
            }
        }
        ImGui::Separator();


        ImGui::Text("Shared options:");
        {
            bool showCube = planetEntity->showCube;
            ImGui::Checkbox("Show as cube       (c)", &showCube);
            if (showCube != planetEntity->showCube) {
                planetEntity->showCube = showCube;
                updateScene = true;
            }
        }
        {
            bool showRegionBounds = planetEntity->showRegionBounds;
            ImGui::Checkbox("Show Region Bounds (b)", &showRegionBounds);
            if (showRegionBounds != planetEntity->showRegionBounds) {
                planetEntity->showRegionBounds = showRegionBounds;
                updateScene = true;
            }
        }
        {
            bool doWarp = planetEntity->doWarp;
            ImGui::Checkbox("Warp texture       (v)", &doWarp);
            if (doWarp != planetEntity->doWarp) {
                planetEntity->doWarp = doWarp;
                updateScene = true;
            }
        }
        ImGui::Separator();

        ImGui::Text("Generator setting:");
        {
            // resolution
            int resolution = planetEntity->getResolution();
            ImGui::PushItemWidth(100);
            ImGui::InputInt("Resolution -(o) +(p)", &resolution);
            if (resolution != planetEntity->getResolution()) {
                planetEntity->setResolution(resolution);
                updateScene = true;
            }
        }
        {
            // jitter
            float jitter = planetEntity->getJitter();
            // ImGui::PushItemWidth(100);
            ImGui::InputFloat("Jitter     -(k) +(l)", &jitter, 0.1f);
            if (jitter != planetEntity->getJitter()) {
                planetEntity->setJitter(jitter);
                updateScene = true;
            }
        }
        {
            // number of plates
            int numberOfPlates = planetEntity->getNumberOfPlates();
            ImGui::PushItemWidth(100);
            ImGui::InputInt("Plates     -(n) +(m)", &numberOfPlates);
            if (numberOfPlates != planetEntity->getNumberOfPlates()) {
                planetEntity->setNumberOfPlates(numberOfPlates);
                updateScene = true;
            }
        }
        ImGui::Separator();

        // plate expand step
        ImGui::Text("Debug control:");
        {
            bool stepPlates = planetEntity->getStepPlates();
            ImGui::Checkbox("", &stepPlates);
            if (stepPlates != planetEntity->getStepPlates()) {
                planetEntity->setStepPlates(stepPlates);
            }
            ImGui::SameLine();
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
    if (val == vt::types::UndefinedVT) {
        return -1;
    }
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
