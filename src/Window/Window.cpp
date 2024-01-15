#include "Window.h"
#include <stb_image.h>
#include <iostream>
#include "../Constants.h"


std::unique_ptr<Window> Window::instance(nullptr);

Window::Window()
    : window(nullptr), initialized(GLFW_FALSE), deltaTime(0.0f), deltaTimeMultiplier(1.0f), fpsCap(0),
     windowWidth(DEFAULT_WINDOW_WIDTH), windowHeight(DEFAULT_WINDOW_HEIGHT),
     windowDimensionsChanged(false), windowIsFocused(true) {}

Window::~Window()
{
    if (initialized)
        glfwTerminate();
    if (window)
        glfwDestroyWindow(window);
}

bool Window::createInstance(const char * windowName, const char * iconPath, int width, int height)
{
    if ((initialized = glfwInit()) == GLFW_FALSE) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    windowWidth = width;
    windowHeight = height;

    if ((window = glfwCreateWindow(windowWidth, windowHeight, windowName, nullptr, nullptr)) == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        return false;
    }

    glfwMakeContextCurrent(window);

    // Vsync
    glfwSwapInterval(1);

    if (iconPath) {
        GLFWimage icon;
        int numChannels;
        icon.pixels = stbi_load(iconPath, &icon.width, &icon.height, &numChannels, 4); // rgba 4 channels
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

bool Window::renderWindow(std::function<bool()> loopFunction)
{
    while (!glfwWindowShouldClose(window)) {

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
        glfwPollEvents();
    }

    return true;
}

float Window::getDeltaTime() const
{
    return deltaTime * deltaTimeMultiplier;
}

float Window::getDeltaTimeNoMultiplier() const
{
    return deltaTime;
}

int Window::getWindowWidth() const
{
    return windowWidth;
}

int Window::getWindowHeight() const
{
    return windowHeight;
}

bool Window::isWindowDimensionsChanged() const
{
    return windowDimensionsChanged;
}

bool Window::isWindowFocused() const
{
    return windowIsFocused;
}

void Window::setTimeMultiplier(float newMult)
{
    deltaTimeMultiplier = newMult;
}

const float& Window::getTimeMultiplier() const
{
    return deltaTimeMultiplier;
}

Window * Window::Init(const char * windowName, const char * iconPath, int width, int height)
{
    Window * window = new Window();
    if (window->createInstance(windowName, iconPath, width, height))
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
    windowWidth = newWidth;
    windowHeight = newHeight;
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

bool Window::handleLoopIteration()
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

Window * Window::getInstance()
{
    return instance.get();
}