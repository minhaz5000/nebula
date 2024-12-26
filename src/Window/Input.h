#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <memory>

// Enum for key states
enum class InputKey : unsigned char {
    Released      = 0, // Released (Default State)
    JustPressed   = 1, // Just pressed and about to go InputKey::Pressed
    Pressed       = 2, // Maintaining pressure
    JustReleased  = 3, // Just released and about to go InputKey::Released
    InputKeyError = 4
};

class Input {
private:

    // Keyboard
    InputKey keys[GLFW_KEY_LAST + 1];   // Array to track key states
    int lastIndex;                      // Index of the last pressed/released key

    // Mouse
    bool mouseMoved;                // Flag indicating whether the mouse has moved
    bool mouseScrollMoved;          // Flag indicating whether the mouse wheel has moved
    glm::vec2 lastPosition;         // Last recorded mouse position
    glm::vec2 positionOffset;       // Offset of the mouse position from the last frame
    glm::vec2 scrollOffset;         // Offset of the mouse scroll

    static std::unique_ptr<Input> instance;

    // Callback functions
    void InputKeyCallback(GLFWwindow * window, int key, int scancode, int action, int mode);
    void InputMouseCallback(GLFWwindow * window, double xpos, double ypos);
    void InputScrollCallback(GLFWwindow * window, double xoffset, double yoffset);

    static void staticInputKeyCallback(GLFWwindow * window, int key, int scancode, int action, int mode);
    static void staticInputMouseCallback(GLFWwindow * window, double xpos, double ypos);
    static void staticInputScrollCallback(GLFWwindow * window, double xoffset, double yoffset);

    Input();    // Constructor
    bool createInstance(GLFWwindow * window);
    
public:
    static Input * Init(GLFWwindow * window);           // Initialize input states
    static Input * getInstance();                       // Get Input instance
    InputKey key(unsigned int index) const;             // Get key state
    void setPosition(glm::vec2 mousePos);               // Set Mouse position
    void setPositionOffset(glm::vec2 mouseOffset);      // Set Mouse offset
    glm::vec2 getPosition() const;                      // Get mouse position
    glm::vec2 getPositionOffset() const;                // Get mouse position offset
    glm::vec2 getWheelOffset() const;                   // Get mouse wheel offset
    bool mouseHasMoved() const;                         // Check if the mouse has moved
    bool mouseScrollHasMoved() const;                   // Check if the mouse wheel has moved
    void InputCallbackCorrection();
    ~Input();
};
