# Date Modified: 2024-12-26

cmake_minimum_required(VERSION 3.20)

project(
  Nebula
  VERSION 1.0
  DESCRIPTION "A Fractal Renderer"
  LANGUAGES CXX C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. "
  )
endif()

# Default Build type if not specified (set to "Release")
set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(
    STATUS
      "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE
      "${default_build_type}"
      CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
                                               "MinSizeRel" "RelWithDebInfo")
endif()
# GraphicsInterface
add_subdirectory(external/GraphicsInterface)

# Add sources and link libraries
add_executable(
  Nebula
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
  src/FractalRenderer.h)

target_link_libraries(Nebula PUBLIC GraphicsInterface::GraphicsInterface)

# Copy resource folder to build dir
add_custom_target(
  copy_resources ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/resources
          ${PROJECT_BINARY_DIR}/resources
  COMMENT "Copying resources into binary directory")

add_dependencies(Nebula copy_resources)
