cmake_minimum_required(VERSION 3.12)

add_library(GLAD STATIC
	src/glad.c
	include/glad/glad.h)

target_include_directories(GLAD PUBLIC include/)
# target_compile_features(GLAD PRIVATE PROPERTY C_STANDARD 99)
