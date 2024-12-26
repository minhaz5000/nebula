# Date Modified: 2024-12-26

cmake_minimum_required(VERSION 3.20)

project(
  glm
  VERSION 1.0.1
  DESCRIPTION "OpenGL Math Library"
  LANGUAGES CXX)

set(GLM_DIR "${CMAKE_CURRENT_SOURCE_DIR}/glm")

set(GLM_BUILD_TESTS OFF)
set(BUILD_SHARED_LIBS OFF)

# GLM
add_subdirectory(${GLM_DIR})
