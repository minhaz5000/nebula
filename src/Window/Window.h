#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <memory>

class Window {
private:
    GLFWwindow * window;
    GLboolean initialized;
    float deltaTime;
    float deltaTimeMultiplier;
    unsigned int fpsCap;
    int width;
    int height;
    bool windowDimensionsChanged;
    bool windowIsFocused;
    static std::unique_ptr<Window> instance;

public:

    Window();

    // Start the window loop and execute the provided function
    bool Loop(std::function<bool()> loopFunction);

    // Get the delta time with multiplier applied
    float DeltaTime() const;

    // Get the delta time without multiplier applied
    float DeltaTimeNoMultiplier() const;

    // Get the current width of the window
    int WindowWidth() const;

    // Get the current height of the window
    int WindowHeight() const;

    // Check if window dimensions have changed
    bool WindowDimensionsChanged() const;

    // Check if the window is focused
    bool IsWindowFocused() const;

    // Set the delta time multiplier
    void SetTimeMultiplier(float newMult);

    // Get the delta time multiplier
    const float& GetTimeMultiplier() const;

    // Initialize the window and return the instance
    static Window * Init(const char * windowName, const char * iconPath = nullptr);

    // Get the window instance
    GLFWwindow * getWindow();

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
    bool HandleLoopIteration();

    // Singleton Pattern here -> create a window
    bool Initialize(const char * windowName, const char * iconPath = nullptr);
};
