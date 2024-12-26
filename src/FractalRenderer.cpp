#include "FractalRenderer.h"
#include "Constants.h"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include <cstdio>
#include <glm/common.hpp>
#include <glm/gtc/type_ptr.hpp>

FractalRenderer::FractalRenderer()
    : enableGUI(true),
      pauseRendering(false),
      timeScale(1.0),
      fractalCenter(0.0f, 0.0f),
      fractalScale(1.0f),
      fractalConstant(0.0f, 0.0f),
      iterations(100),
      color1(1.0f, 0.0f, 0.0f),
      color2(0.0f, 0.0f, 1.0f),
      color3(0.0f, 1.0f, 0.0f),
      escapeRadius(4.0f)
{
    // Initialize a GLFW window
    window = Window::Init(Constants::Window::windowName, Constants::Window::windowIcon);
    if (!window) exit(EXIT_FAILURE);

    // Initialize Input Callbacks to the window
    input = Input::Init(window->getWindow());

    // Renderer for Fractals
    renderer = new Renderer();
    renderer->loadShaders(Constants::Shaders::ShaderFiles);

    gui = new GUI(window->getWindow());

    useMandelbrotFractal();  // Default Shader Selected
}

FractalRenderer::~FractalRenderer() {}

void FractalRenderer::renderFractal()
{

    auto guiLoop = [&]() -> bool {
        const float width  = 320.0f;
        const float height = 475.0f;
        ImGui::SetNextWindowSize({width, height}, ImGuiCond_::ImGuiCond_Always);
        ImGui::SetNextWindowPos({ImGui::GetIO().DisplaySize.x - 20.0f - width, 20.0f},
                                ImGuiCond_::ImGuiCond_Always);

        if (ImGui::Begin("Settings:")) {
            ImGui::Checkbox("Enable/Disable GUI (Press T)", &enableGUI);
            if (ImGui::BeginCombo("Fractal Type", renderer->getCurrentShaderName().c_str())) {
                if (ImGui::Selectable("Mandelbrot",
                                      renderer->getCurrentShaderName() == "Mandelbrot")) {
                    useMandelbrotFractal();
                }
                if (ImGui::Selectable("Julia", renderer->getCurrentShaderName() == "Julia")) {
                    useJuliaFractal();
                }
                if (ImGui::Selectable("Julia Complex Dynamics", renderer->getCurrentShaderName() ==
                                                                    "Julia Complex Dynamics")) {
                    useJuliaComplexDynamicsFractal();
                }
                if (ImGui::Selectable("Newton", renderer->getCurrentShaderName() == "Newton")) {
                    useNewtonFractal();
                }
                ImGui::EndCombo();
            }

            // Default Callback for every fractal
            defaultCallback();

            if (renderer->getCurrentShaderName() == "Mandelbrot") {
                // Mandelbrot Specific GUI
                mandelbrotCallback();
            }
            else if (renderer->getCurrentShaderName() == "Julia") {
                juliaCallback();
            }
            else if (renderer->getCurrentShaderName() == "Julia Complex Dynamics") {
                juliaComplexDynamicsCallback();
            }
            else if (renderer->getCurrentShaderName() == "Newton") {
                newtonCallback();
            }
            // GUI logic for fractal settings
            ImGui::End();  // Close the Settings window
        }
        return true;
    };

    gui->addCallback(guiLoop);

    float currentTime = glfwGetTime();

    auto windowLoop = [&]() -> bool {
        // Set fractal-specific uniforms in the shader
        renderer->useCurrentShader();
        renderer->getCurrentShader()->setUniformVec2("u_fractalCenter", fractalCenter);
        renderer->getCurrentShader()->setUniformFloat("u_fractalScale", fractalScale);
        renderer->getCurrentShader()->setUniformVec2("u_fractalConstant", fractalConstant);
        renderer->getCurrentShader()->setUniformVec2(
            "u_resolution", glm::vec2{window->getWindowWidth(), window->getWindowHeight()});
        renderer->getCurrentShader()->setUniformInt("u_iterations", iterations);
        renderer->getCurrentShader()->setUniformVec3("u_color1", color1);
        renderer->getCurrentShader()->setUniformVec3("u_color2", color2);
        if (renderer->getCurrentShaderName() == "Julia") {
            renderer->getCurrentShader()->setUniformVec3("u_color3", color3);
        }
        renderer->getCurrentShader()->setUniformFloat("u_escapeRadius", escapeRadius);

        // Additional rendering logic specific to fractals

        // Enable/Disable GUI
        if (input->key(GLFW_KEY_T) == InputKey::JustPressed) {
            enableGUI = !enableGUI;
        }

        // Adjust time scaling based on user input
        if (input->key(GLFW_KEY_UP) == InputKey::Pressed) {
            timeScale *= 1.1f;  // Increase time scaling by 10% with each frame
        }
        if (input->key(GLFW_KEY_DOWN) == InputKey::Pressed) {
            timeScale *= 0.9f;  // Decrease time scaling by 10% with each frame
        }

        if (input->key(GLFW_KEY_W) == InputKey::Pressed) {
            fractalCenter.y += 0.1;
        }
        if (input->key(GLFW_KEY_A) == InputKey::Pressed) {
            fractalCenter.x -= 0.1;
        }
        if (input->key(GLFW_KEY_S) == InputKey::Pressed) {
            fractalCenter.y -= 0.1;
        }
        if (input->key(GLFW_KEY_D) == InputKey::Pressed) {
            fractalCenter.x += 0.1;
        }
        if (input->key(GLFW_KEY_X) == InputKey::Pressed) {
            fractalCenter = {0., 0.};
            fractalScale  = 1.0;
        }

        // if (input->key(GLFW_MOUSE_BUTTON_LEFT) == InputKey::Pressed) {
        //     fractalCenter += input->getPositionOffset();
        // }

        // Pause/Resume Rendering
        if (input->key(GLFW_KEY_P) == InputKey::JustPressed) {
            pauseRendering = !pauseRendering;
        }

        if (!pauseRendering) {
            currentTime = glfwGetTime() * timeScale;
            ;
            renderer->getCurrentShader()->setUniformFloat("u_time", currentTime);
        }

        // Zoom in/out using the mouse wheel
        if (input->mouseScrollHasMoved()) {
            fractalScale *=
                exp(input->getWheelOffset().y * 0.1f);  // Adjust the scaling factor as needed
        }

        // Change color algorithm based on user input
        if (input->key(GLFW_KEY_C) == InputKey::JustPressed) {
            // Cycle to the next color algorithm
            color1 = glm::vec3{0., 0., 0.};
            color2 = glm::vec3{1.0, 1.0, 1.0};
        }

        renderer->draw();

        if (enableGUI) {
            gui->drawGUI();
        }

        input->InputCallbackCorrection();
        return true;
    };

    window->renderWindow(windowLoop);
}

void FractalRenderer::useJuliaFractal()
{
    // Additional setup or logic for Julia fractal
    // ...

    // Set the current shader to Julia fractal shader
    renderer->setCurrentShader("Julia");
    fractalConstant = glm::vec2{-0.12256, 0.74486};
    color1          = glm::vec3(0.9, 0.2, 0.1);
    color2          = glm::vec3(1.0, 1.0, 1.0);
    color3          = glm::vec3(0.1, 0.2, 0.9);
}

void FractalRenderer::useNewtonFractal()
{
    // Additional setup or logic for Julia fractal
    // ...

    // Set the current shader to Julia fractal shader
    renderer->setCurrentShader("Newton");
}

void FractalRenderer::useMandelbrotFractal()
{
    // Additional setup or logic for Mandelbrot fractal
    // ...

    // Set the current shader to Mandelbrot fractal shader
    escapeRadius = 4.0f;
    renderer->setCurrentShader("Mandelbrot");
}

void FractalRenderer::useJuliaComplexDynamicsFractal()
{
    renderer->setCurrentShader("Julia Complex Dynamics");
}

// In the FractalRenderer class implementation

bool FractalRenderer::defaultCallback()
{
    ImGui::Text("Fractal Settings:");

    // Common fractal parameters
    ImGui::SliderFloat2("Center", glm::value_ptr(fractalCenter), -2.0f, 2.0f);
    ImGui::SliderFloat("Scale", &fractalScale, 0.1f, 100.0f);
    ImGui::SliderInt("Iterations", &iterations, 1, 500);

    return true;
}

bool FractalRenderer::juliaCallback()
{

    // Julia-specific GUI callback logic
    ImGui::Separator();
    ImGui::SliderFloat2("Julia Constant", glm::value_ptr(fractalConstant), -2.0f, 2.0f);
    ImGui::SliderFloat("Escape Radius", &escapeRadius, 0.1f, 8.0f);
    // Color customization
    ImGui::Text("Color Settings:");
    ImGui::ColorEdit3("Color 1", glm::value_ptr(color1));
    ImGui::ColorEdit3("Color 2", glm::value_ptr(color2));
    ImGui::ColorEdit3("Color 3", glm::value_ptr(color3));
    return true;
}

bool FractalRenderer::mandelbrotCallback()
{
    // Mandelbrot-specific GUI callback logic
    // Color customization
    ImGui::Separator();
    ImGui::Text("Color Settings:");
    ImGui::ColorEdit3("Color 1", glm::value_ptr(color1));
    ImGui::ColorEdit3("Color 2", glm::value_ptr(color2));
    return true;
}

bool FractalRenderer::newtonCallback() { return true; }

bool FractalRenderer::juliaComplexDynamicsCallback() { return true; }
