# Nebula Fractal Renderer

Nebula is a fractal renderer built using GLAD, GLFW, GLM, and ImGui. It generates stunning visualizations of fractals using modern OpenGL.

## Features

- Real-time rendering of fractals.
- Interactive user interface with Dear ImGui.
- GLAD for OpenGL loading.
- Utilizes GLFW for window management.
- GLM for mathematics operations.
- CMake for cross-platform build system.

## Dependencies

- [GLAD](https://github.com/Dav1dde/glad)
- [GLFW](https://github.com/glfw/glfw)
- [GLM](https://github.com/g-truc/glm)
- [ImGui](https://github.com/ocornut/imgui)

## Build Instructions

   ```
   cmake -S . -B build
   cmake --build build
   cd build
   ./Nebula
   ```
