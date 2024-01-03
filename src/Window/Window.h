#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <memory>

#define DEFAULT_WINDOW_WIDTH 1280
#define DEFAULT_WINDOW_HEIGHT 720

class Window {
private:
    GLFWwindow * window;
    GLboolean initialized;
    float deltaTime;
    float deltaTimeMultiplier;
    unsigned int fpsCap;
    int windowWidth;
    int windowHeight;
    bool windowDimensionsChanged;
    bool windowIsFocused;
    static std::unique_ptr<Window> instance;

public:

    Window();

    // Start the window loop and execute the provided function
    bool renderWindow(std::function<bool()> loopFunction);

    // Get the delta time with multiplier applied
    float getDeltaTime() const;

    // Get the delta time without multiplier applied
    float getDeltaTimeNoMultiplier() const;

    // Get the current width of the window
    int getWindowWidth() const;

    // Get the current height of the window
    int getWindowHeight() const;

    // Check if window dimensions have changed
    bool isWindowDimensionsChanged() const;

    // Check if the window is focused
    bool isWindowFocused() const;

    // Set the delta time multiplier
    void setTimeMultiplier(float newMult);

    // Get the delta time multiplier
    const float& getTimeMultiplier() const;

    // Initialize the window and return the instance
    static Window * Init(const char * windowName, const char * iconPath = nullptr,
        int width = DEFAULT_WINDOW_WIDTH, int height = DEFAULT_WINDOW_HEIGHT);

    // Get the window instance
    GLFWwindow * getWindow();

    static Window * getInstance();

    ~Window();

private:

    // Callback function for window resize
    void framebufferSizeCallback(GLFWwindow * window, int newWidth, int newHeight);

    // Callback for window focus
    void windowFocusCallback(GLFWwindow * window, int focusState);

    // Callback function for window resize (Static)
    static void staticFramebufferSizeCallback(GLFWwindow * window, int newWidth, int newHeight);

    // Callback for window focus (Static)
    static void staticWindowFocusCallback(GLFWwindow * window, int focusState);

    // Handle one iteration of the loop
    bool handleLoopIteration();

    // Singleton Pattern here -> create a window
    bool createInstance(const char * windowName, const char * iconPath = nullptr,
     int width = DEFAULT_WINDOW_WIDTH, int height = DEFAULT_WINDOW_HEIGHT);
};
