#include "Window/Window.h"
#include "Window/Input.h"
#include "Window/GUI.h"
#include "Renderer/Renderer.h"
#include "Constants.h"
#include "Shader/Shader.h"
#include <cstdio>

int main()
{
    // Initialize a GLFW window
    Window * window = Window::Init(Constants::Window::windowName, nullptr);
    if (!window)
        return EXIT_FAILURE;

    // Initialize Input Callbacks to the window
    Input::Init(window->getWindow());

    // Renderer for Fractals
    Renderer * fractalRenderer = new Renderer();
    fractalRenderer->loadShaders(Constants::Shaders::shaderFiles);

    


    // GUI for Controlling the fractal Renderer
    GUI gui(window->getWindow());

    bool enableGUI = true;
    bool show_demo_window = true;

    auto guiLoop = [&]() -> bool {
        
        if (show_demo_window) {
            ImGui::ShowDemoWindow(&show_demo_window);
        }
        return true;
    };

    gui.addCallback(guiLoop);

    fractalRenderer->setCurrentShader(Constants::Shaders::ShaderID::Mandelbrot);
    auto windowLoop = [&]() -> bool {
        
        fractalRenderer->useCurrentShader();
        GLfloat currentTime = glfwGetTime();
        fractalRenderer->getCurrentShader()->setUniformFloat("iTime", currentTime);
        fractalRenderer->draw();
        if (enableGUI) {
           gui.draw();
        }
        return true;
    };

    window->Loop(windowLoop);


    return 0;
}
