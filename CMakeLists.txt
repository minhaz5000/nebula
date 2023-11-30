cmake_minimum_required(VERSION 3.12)

project(Nebula VERSION 1.0
	DESCRIPTION "A Fractal Renderer"
	LANGUAGES CXX C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set Defaut Build Type
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
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# Find the required packages
find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")
find_package(GLFW REQUIRED)
message(STATUS "Found GLFW in ${GLFW_INCLUDE_DIR}")
find_package(OpenGL REQUIRED)

# Add GLAD----------------------------------------------------------------------------------------------------------
add_subdirectory(lib/glad)

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

# Set CXX Standard
target_link_libraries(Nebula
  PRIVATE GLAD
  PRIVATE ${GLFW_LIBRARY}
  PRIVATE OpenGL::OpenGL
  )
target_include_directories(Nebula PUBLIC ${GLFW_INCLUDE_DIR})

target_compile_features(Nebula PUBLIC cxx_std_11)
set_target_properties(Nebula PROPERTIES
  CXX_EXTENSIONS OFF
  RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}"
  )



