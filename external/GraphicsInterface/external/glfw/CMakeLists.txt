cmake_minimum_required(VERSION 3.20)

set(GLFW_DIR ${CMAKE_CURRENT_SOURCE_DIR}/glfw-3.4)

set(BUILD_SHARED_LIBS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)
add_subdirectory(${GLFW_DIR})
