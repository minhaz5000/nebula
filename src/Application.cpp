#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "Shader/Shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}


void process_input(GLFWwindow* window, float& zoom) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set GLFW options (use OpenGL 4.6 Core Profile)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Mandelbrot Fractal", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Set up viewport and callback functions
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Create Mandelbrot shader
    Shader mandelbrotShader("ShaderFiles/Mandelbrot/Mandelbrot_vertex_shader.glsl", "ShaderFiles/Mandelbrot/Mandelbrot_fragment_shader.glsl");

    // Set up fullscreen quad
    unsigned int fullscreenQuadVAO, fullscreenQuadVBO;
    float quadVertices[] = {
        -1.0f, -1.0f, 0.0f, 1.0f,
         1.0f, -1.0f, 0.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 1.0f,
         1.0f, -1.0f, 0.0f, 1.0f,
         1.0f,  1.0f, 0.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 1.0f
    };

    glGenVertexArrays(1, &fullscreenQuadVAO);
    glGenBuffers(1, &fullscreenQuadVBO);

    glBindVertexArray(fullscreenQuadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, fullscreenQuadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    float zoom = 1.0f;
    // Main render loop
    while (!glfwWindowShouldClose(window)) {
        process_input(window, zoom);

        // Use Mandelbrot shader
        mandelbrotShader.use();

        // Set time uniform to create animation
        float currentTime = glfwGetTime();
        mandelbrotShader.setFloat("iTime", currentTime);

        mandelbrotShader.setFloat("zoom", zoom);


        // Clear the screen
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render fullscreen quad
        glBindVertexArray(fullscreenQuadVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        // Swap buffers
        glfwSwapBuffers(window);
    }

    // Cleanup
    glDeleteVertexArrays(1, &fullscreenQuadVAO);
    glDeleteBuffers(1, &fullscreenQuadVBO);
    glfwTerminate();

    return 0;
}