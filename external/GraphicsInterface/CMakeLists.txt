# Date Modified: 2024-12-26

cmake_minimum_required(VERSION 3.20)

project(
  GraphicsInterface
  DESCRIPTION "Interface Library for Graphics Programming in C and C++"
  LANGUAGES C CXX)

option(BUILD_USING_LOCAL_LIBS "Use the local libs to build the library" ON)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. "
  )
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
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

# OpenGL
find_package(OpenGL REQUIRED)

add_library(GraphicsInterface INTERFACE)

if(BUILD_USING_LOCAL_LIBS)
  add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/external")
endif()

target_link_libraries(GraphicsInterface INTERFACE OpenGL::GL glad glfw
                                                  glm::glm imgui stb_image)
add_library(GraphicsInterface::GraphicsInterface ALIAS GraphicsInterface)
