cmake_minimum_required(VERSION 3.12...3.27)

project(Nebula VERSION 1.0
	DESCRIPTION "A Fractal Renderer"
	LANGUAGES CXX C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Default Build Type
set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
      STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()


# CMake Modulepth setfor Find*.cmake
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

# Find the required packages
find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")
find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")
find_package(OpenGL REQUIRED)

# Add GLAD----------------------------------------------------------------------------------------------------------
add_library(GLAD STATIC lib/glad/src/glad.c)
target_include_directories(GLAD PUBLIC lib/glad/include)

# Variable LIBS for all the libraries needed to link
set(LIBS OpenGL::OpenGL GLAD ${GLFW3_LIBRARY})

add_executable(${PROJECT_NAME}
  src/Application.cpp
  src/ComplexNumber.cpp
  src/ComplexNumber.h
  src/Pixel.cpp
  src/Pixel.h
  src/Fractal.cpp
  src/Fractal.h
  src/FractalSet.cpp
  src/FractalSet.h)

# Set CXX Standard
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})


