#pragma once

#include "Renderer/Renderer.h"
#include "Window/Input.h"
#include "Window/Window.h"
#include "Window/GUI.h"
#include <glm/fwd.hpp>

class FractalRenderer {
private:
    Renderer * renderer;
    Input * input;
    Window * window;
    GUI * gui;

    // GUI variables
    bool enableGUI;
    bool pauseRendering;
    float timeScale;

    // Fractal Parameters
    glm::vec2 fractalCenter;
    float fractalScale;
    glm::vec2 fractalConstant;
    int iterations;
    glm::vec3 color1;
    glm::vec3 color2;
    glm::vec3 color3;
    float escapeRadius;

public:
    FractalRenderer();
    ~FractalRenderer();

    // Setters for fractal parameters
    void setFractalCenter(const glm::vec2 & center);
    void setFractalScale(float scale);
    void setJuliaC(const glm::vec2 & juliaC);
    void setIterations(int iterations);
    void setColor1(const glm::vec3 & color);
    void setColor2(const glm::vec3 & color);

    // Render the current fractal
    void renderFractal();

    // Switch to different fractal types
    void useJuliaFractal();
    void useMandelbrotFractal();
    void useNewtonFractal();
    void useJuliaComplexDynamicsFractal();

    // GUI callback functions
    bool defaultCallback();
    bool juliaCallback();
    bool mandelbrotCallback();
    bool newtonCallback();
    bool juliaComplexDynamicsCallback();
};
