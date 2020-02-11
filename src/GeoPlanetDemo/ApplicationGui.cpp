
#include <geGL/geGL.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vendor/imgui/imgui.h>
#include <vendor/imgui/imgui_impl_sdl.h>
#include <vendor/imgui/imgui_impl_opengl3.h>

#include <GeoPlanetDemo/core/Camera.h>

#include <GeoPlanetDemo/ApplicationGui.h>
#include <GeoPlanetDemo/sdl/SDLGlMainLoop.h>
#include <GeoPlanetDemo/sdl/SDLPerformance.h>

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

    // build main invisible window (left panel)
    ImGui::SetNextWindowPos({0,0});
    ImGui::SetNextWindowSize({
        300.0f,                                          // width
        (float)application->mainLoop->getWindow()->getHeight()  // height
	});
    ImGui::Begin("menu", nullptr,
        ImGuiWindowFlags_NoTitleBar
        | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoBackground
    );

    // FPS plotting
    auto performance = application->mainLoop->getPerformance();
    char text[20];
	sprintf_s(text, 20, "FPS: %g", performance->getFrames());
	float fpsHistory[sdl::SDLPerformance::HISTORY_LEN];
    performance->getHistory(fpsHistory);
	ImGui::PlotLines(text, fpsHistory, sdl::SDLPerformance::HISTORY_LEN);

    // controls


	ImGui::End();
    drawTearDown();
}

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
