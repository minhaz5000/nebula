cmake_minimum_required(VERSION 3.12)

set(GLAD_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library(glad ${GLAD_DIR}/src/glad.c)

target_include_directories(glad PUBLIC include/)
# target_compile_features(glad PRIVATE PROPERTY C_STANDARD 99)
