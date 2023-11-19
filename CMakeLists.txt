cmake_minimum_required(VERSION 3.12)

# Project name - should not contain whitespace 
project(nebula)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Turn on Compiler Warnings
add_compile_options(-Wall -Wextra)

# Add source files
file(GLOB_RECURSE SOURCE_FILES 
    ${CMAKE_SOURCE_DIR}/src/*.c
    ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Add header files
file(GLOB_RECURSE HEADER_FILES 
    ${CMAKE_SOURCE_DIR}/src/*.h
    ${CMAKE_SOURCE_DIR}/src/*.hpp)

# Define the executable
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

set(CMAKE_BUILD_TYPE Debug)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# We need a CMAKE_DIR with some code to find external dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#######################################
# LOOK for the packages that we need! #
#######################################


  
  # note that the order is important for setting the libs
  # use pkg-config --libs $(pkg-config --print-requires --print-requires-private glfw3) in a terminal to confirm
  set(LIBS ${GLFW3_LIBRARY} X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL dl pthread freetype ${ASSIMP_LIBRARY})
  set (CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")

# OpenGL
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

# X11
# find_package(X11 REQUIRED)

# GLM
find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")

# GLFW
find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")

# GLAD
add_library(GLAD "thirdparty/glad.c")

# Put all libraries into a variable
# set(LIBS ${GLFW3_LIBRARY} ${OPENGL_LIBRARY} GLAD X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL dl pthread freetype)
set(LIBS ${GLFW3_LIBRARY} ${OPENGL_LIBRARY} GLAD X11)

# Define the include DIRs
include_directories(
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/include"
)

# Define the link libraries
target_link_libraries(${PROJECT_NAME} ${LIBS})


# Add target to run executable 
add_custom_target(run
    COMMAND ./nebula  # Specify the correct executable name and location
    DEPENDS nebula 
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

