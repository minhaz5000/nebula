cmake_minimum_required(VERSION 3.20)

project(Nebula VERSION 1.0
	DESCRIPTION "A Fractal Renderer"
	LANGUAGES CXX C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# OpenGL
find_package(OpenGL REQUIRED)

# GLFW Library
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glfw)

# GLAD
add_subdirectory(external/glad)

add_executable(Nebula
  src/Application.cpp
  src/ComplexNumber.cpp
  src/ComplexNumber.h
  src/Pixel.cpp
  src/Pixel.h
  src/Fractal.cpp
  src/Fractal.h
  src/FractalSet.cpp
  src/FractalSet.h
  )

target_link_libraries(Nebula
  PRIVATE GLAD
  PRIVATE glfw
  PRIVATE OpenGL::OpenGL
  )

