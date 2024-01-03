#pragma once

#include <functional>
#include <glm/glm.hpp>

// ImGui includes
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <vector>

class GUI
{
public:
    GUI(GLFWwindow * window);
    ~GUI();
    bool drawGUI();
    void addCallback(std::function<bool()> callbackFunction);

private:
    ImGuiIO * io;
    std::vector<std::function<bool()>> callbacks;

};
