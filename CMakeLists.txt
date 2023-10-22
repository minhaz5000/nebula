cmake_minimum_required(VERSION 3.9)

# Proeject name - should not contain whitespace 
project(nebula)

#========== Global Configurations =============#
#----------------------------------------------#

# Set the C++ standard for all targets (It sets the flags
# (-std=c++11, -std=c++14 ...) on Clang or GCC. and /std=c++17 on MSVC
# OPTIONAL:
#---------------------------------
set(CMAKE_CXX_STANDARD 17)     
# set(CMAKE_VERBOSE_MAKEFILE ON)

# Find the GLFW package
find_package(glfw3 REQUIRED)

#========== Targets Configurations ============#

# Set the binary directory where the executable will be placed
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Build an executable (Unix-like OSes generates ./openglDemo1, on
# Windows ./opengDemo1.exe)
# ..........................................
add_executable(nebula src/main.cpp)


# Set executable dependency libraries
# Equivalent to pass flags -lGL, -lGLU and -lglut 
# Link the GLFW library
target_link_libraries(nebula PRIVATE glfw)

# Add target to run executable 
add_custom_target(run-ex
    COMMAND ./nebula  # Specify the correct executable name and location
    DEPENDS nebula 
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin  # Set the working directory to the "bin" folder
)


