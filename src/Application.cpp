#include "Window/Window.h"
#include "Window/GUI.h"
#include "Renderer/Renderer.h"
#include "FractalRenderer.h"
#include "Constants.h"
#include "Shader/Shader.h"
#include "imgui.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

int main()
{
    // Fractal Renderer
    FractalRenderer myFractal;
    myFractal.renderFractal();
    
    return 0;
}
