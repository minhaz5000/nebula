# Date Modified: 2024-12-26

cmake_minimum_required(VERSION 3.20)

# GLAD
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/glad")

# GLFW
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/glfw")

# GLM
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/glm")

# DearImgui
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/imgui")

# stb_image
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/stb_image")

