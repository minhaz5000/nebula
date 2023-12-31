#include "Window.h"
#include <stb_image.h>
#include <iostream>


std::unique_ptr<Window> Window::instance(nullptr);

Window::Window()
    : window(nullptr), initialized(GLFW_FALSE), deltaTime(0.0f), deltaTimeMultiplier(1.0f), fpsCap(0), width(1280),
 height(720), windowDimensionsChanged(false), windowIsFocused(true) {}

Window::~Window()
{
    if (initialized)
        glfwTerminate();
    if (window)
        glfwDestroyWindow(window);
}

bool Window::Initialize(const char * windowName, const char * iconPath)
{
    if ((initialized = glfwInit()) == GLFW_FALSE) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Anti-Aliasing
    // glfwWindowHint(GLFW_SAMPLES, 4);

    if ((window = glfwCreateWindow(width, height, windowName, nullptr, nullptr)) == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        return false;
    }

    glfwMakeContextCurrent(window);

    // Vsync
    glfwSwapInterval(1);

    if (iconPath) {
        GLFWimage icon;
        int numChannels;
        icon.pixels = stbi_load(iconPath, &icon.width, &icon.height, &numChannels, 0);
        if (icon.pixels) {
            glfwSetWindowIcon(window, 1, &icon);
            stbi_image_free(icon.pixels);
        }
    }

    glfwSetFramebufferSizeCallback(window, staticFramebufferSizeCallback);
    glfwSetWindowFocusCallback(window, staticWindowFocusCallback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Failed to initialize glad" << std::endl;
        return false;
    }
    
    return true;
}

bool Window::Loop(std::function<bool()> loopFunction)
{
    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();

        // Clear the screen
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // if (!HandleLoopIteration())
        //     return false;

        if (!loopFunction())
            return false;

        windowDimensionsChanged = false;
        glfwSwapBuffers(window);
    }

    return true;
}

float Window::DeltaTime() const
{
    return deltaTime * deltaTimeMultiplier;
}

float Window::DeltaTimeNoMultiplier() const
{
    return deltaTime;
}

int Window::WindowWidth() const
{
    return width;
}

int Window::WindowHeight() const
{
    return height;
}

bool Window::WindowDimensionsChanged() const
{
    return windowDimensionsChanged;
}

bool Window::IsWindowFocused() const
{
    return windowIsFocused;
}

void Window::SetTimeMultiplier(float newMult)
{
    deltaTimeMultiplier = newMult;
}

const float& Window::GetTimeMultiplier() const
{
    return deltaTimeMultiplier;
}

Window * Window::Init(const char * windowName, const char * iconPath)
{
    Window * window = new Window();
    if (window->Initialize(windowName, iconPath))
        instance.reset(window);
    else
        delete window;
    return instance.get();
}

GLFWwindow * Window::getWindow()
{
    return window;
}

void Window::framebufferSizeCallback(GLFWwindow * window, int newWidth, int newHeight)
{
    width = newWidth;
    height = newHeight;
    glViewport(0, 0, newWidth, newHeight);
    windowDimensionsChanged = true;
}

void Window::windowFocusCallback(GLFWwindow * window, int focusState)
{
    windowIsFocused = static_cast<bool> (focusState);
}

void Window::staticFramebufferSizeCallback(GLFWwindow * window, int newWidth, int newHeight)
{
    instance->framebufferSizeCallback(window, newWidth, newHeight);
}

void Window::staticWindowFocusCallback(GLFWwindow * window, int focusState)
{
    instance->windowFocusCallback(window, focusState);
}

bool Window::HandleLoopIteration()
{
    GLfloat lastFrame = 0.0f;
    GLfloat currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    if (fpsCap != 0)
    {
        while (deltaTime <= 1.0f / fpsCap)
        {
            currentFrame = glfwGetTime();
            deltaTime += currentFrame - lastFrame;
            lastFrame = currentFrame;
        }
    }

    glfwPollEvents();

    return true;
}
