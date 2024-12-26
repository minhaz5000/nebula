#include "GUI.h"
#include "../Constants.h"
#include <imgui_internal.h>

GUI::GUI(GLFWwindow * window)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO();
    // Setup Platform/Renderer bindings
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(Constants::GUI::GLSL_VERSION);

    // Set custom font
    ImFont* font = io->Fonts->AddFontFromFileTTF(Constants::GUI::arialFont, 18.0f, NULL, io->Fonts->GetGlyphRangesDefault());
    IM_ASSERT(font != nullptr);

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();
}

GUI::~GUI()
{
    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();
}

bool GUI::drawGUI()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    
    for (auto & callback : callbacks)
        if (!callback()) return false;

    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    return true;
}

void GUI::addCallback(std::function<bool()> callbackFunction)
{
    callbacks.push_back(callbackFunction);
}


