cmake_minimum_required(VERSION 3.20)

project(Nebula VERSION 1.0
	DESCRIPTION "A Fractal Renderer"
	LANGUAGES CXX C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

# OpenGL
find_package(OpenGL REQUIRED)

# GLAD
add_subdirectory(external/glad)

# GLFW Library
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glfw)

# OpenGL GLM Library
add_subdirectory(external/glm)

# Dear ImGui Library | Must add GLFW before.
add_subdirectory(external/imgui)

# stb_image Library
add_subdirectory(external/stb_image)

# Add sources and link libraries

add_executable(Nebula
  src/Constants.h
  src/Shader/Shader.cpp
  src/Shader/Shader.h
  src/Window/Input.h
  src/Window/Input.cpp
  src/Window/Window.h
  src/Window/Window.cpp
  src/Window/GUI.h
  src/Window/GUI.cpp
  src/Application.cpp
  src/Renderer/Renderer.h
  src/Renderer/Renderer.cpp
  src/FractalRenderer.cpp
  src/FractalRenderer.h
  )

target_link_libraries(Nebula
  PRIVATE OpenGL::GL
  PRIVATE glad
  PRIVATE glfw
  PRIVATE glm
  PRIVATE imgui
  PRIVATE stb_image
  )

# Copy resource folder to build dir
add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        $<TARGET_FILE_DIR:Nebula>/resources
        COMMENT "Copying resources into binary directory")

add_dependencies(Nebula copy_resources)

