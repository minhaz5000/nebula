# Nebula Fractal Renderer

**Nebula** is a fractal renderer built using GLAD, GLFW, GLM, and ImGui. It generates stunning visualizations of fractals using modern OpenGL.

## Screenshots

### Mandelbrot Set

<img src="screenshots/1.png" alt="Mandelbrot" width="400">
<img src="screenshots/2.png" alt="Mandelbrot" width="400">

### Julia Fractal

<img src="screenshots/3.png" alt="Julia" width="400">
<img src="screenshots/4.png" alt="Julia" width="400">
<img src="screenshots/5.png" alt="Julia" width="400">

### Julia Complex Dynamics

<img src="screenshots/6.png" alt="Julia Complex Dynamics" width="400">

### Newton's Fractal

<img src="screenshots/7.png" alt="Newton's Fractal" width="400">

## Features

- Real-time rendering of fractals.
- Interactive user interface with Dear ImGui.
- GLAD for OpenGL loading.
- GLFW for window management.
- GLM for mathematical operations.
- CMake for cross-platform builds.

### Updated to use GraphicsInterface Library which includes all of the above.

## Dependencies

- [GLAD](https://github.com/Dav1dde/glad)
- [GLFW](https://github.com/glfw/glfw)
- [GLM](https://github.com/g-truc/glm)
- [ImGui](https://github.com/ocornut/imgui)

## Build Instructions

```bash
cmake -S . -B build
cmake --build build
cd build
./Nebula
```
