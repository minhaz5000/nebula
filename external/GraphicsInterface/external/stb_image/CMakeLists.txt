# Date Modified: 2024-12-26

cmake_minimum_required(VERSION 3.20)

set(STB_IMAGE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library(
  stb_image
  ${STB_IMAGE_DIR}/src/stb_image.cpp ${STB_IMAGE_DIR}/src/stb_image_write.cpp
  ${STB_IMAGE_DIR}/include/stb_image.h
  ${STB_IMAGE_DIR}/include/stb_image_write.h)

target_include_directories(stb_image PUBLIC ${STB_IMAGE_DIR}/include)
