
#include <geGL/geGL.h>

#include <vendor/imgui/imgui.h>
#include <vendor/imgui/imgui_impl_sdl.h>
#include <vendor/imgui/imgui_impl_opengl3.h>

#include <GeoPlanetDemo/ApplicationGui.h>
#include <GeoPlanetDemo/sdl/SDLGlMainLoop.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    return ImGui_ImplSDL2_ProcessEvent(&event);
}

void ApplicationGui::onFrameUpdate()
{
}

void ApplicationGui::draw()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(application->mainLoop->getWindow()->getWindow());
	ImGui::NewFrame();

	// Create a window called "My First Tool", with a menu bar.
	bool my_tool_active = true;
	ImGui::Begin("My First Tool", &my_tool_active, ImGuiWindowFlags_MenuBar);
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
			if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
			if (ImGui::MenuItem("Close", "Ctrl+W")) { my_tool_active = false; }
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	// Edit a color (stored as ~4 floats)
    float col[4] = {0.5f, 0.5f, 0.5f, 0};
	ImGui::ColorEdit4("Color", col);

	// Plot some values
	const float my_values[] = { 0.2f, 0.1f, 1.0f, 0.5f, 0.9f, 2.2f };
	ImGui::PlotLines("Frame Times", my_values, IM_ARRAYSIZE(my_values));

	// Display contents in a scrolling region
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "Important Stuff");
	ImGui::BeginChild("Scrolling");
	for (int n = 0; n < 50; n++)
		ImGui::Text("%04d: Some text", n);
	ImGui::EndChild();
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
