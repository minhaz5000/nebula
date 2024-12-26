# Date Modified: 2024-12-26

cmake_minimum_required(VERSION 3.20)

set(GLAD_DIR ${CMAKE_CURRENT_SOURCE_DIR})
add_library(glad ${GLAD_DIR}/src/glad.c)
target_include_directories(glad PUBLIC ${GLAD_DIR}/include)
