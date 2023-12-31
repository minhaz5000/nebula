#include "Input.h"

std::unique_ptr<Input> Input::instance(nullptr);

Input::Input() : keys{InputKey::Released}, lastIndex{-1}, mouseMoved(false), mouseScrollMoved(false),
lastPosition(0.0), positionOffset(0.0), scrollOffset(0.0f, 0.0f) {}

// Initialize GLFW callbacks
bool Input::Initialize(GLFWwindow * window)
{
    glfwSetCursorPosCallback(window, staticInputMouseCallback);
    glfwSetScrollCallback(window, staticInputScrollCallback);
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    lastPosition = glm::vec2{xpos, ypos};
    return true;
}

// Get key state
InputKey Input::key(unsigned int index) const
{
    if (index >= 1024)
        return InputKey::InputKeyError;

    return keys[index];
}

// Correct input-related callbacks
void Input::InputCallbackCorrection()
{
    if (lastIndex >= 0 && lastIndex < 1024) {
        keys[lastIndex] = static_cast<InputKey>((static_cast<unsigned char>(keys[lastIndex]) + 1) % 4);
        lastIndex = -1;
    }
    resetState();
}

// Callback for mouse movement
void Input::InputMouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    InputCallbackCorrection();  // Correct any previous input callbacks
    updatePosition(xpos, ypos);
}

// Callback for mouse scroll
void Input::InputScrollCallback(GLFWwindow * window, double xoffset, double yoffset)
{
    InputCallbackCorrection();  // Correct any previous input callbacks
    resetState();  // Reset the mouse state when scrolling
    positionOffset = glm::vec2{xoffset, yoffset};
}

// Callback for keyboard input
void Input::InputKeyCallback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
    InputCallbackCorrection();  // Correct any previous input callbacks

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    if (key >= 0 && key < 1024) {
        switch (action) {
            case GLFW_PRESS:
                keys[key] = InputKey::JustPressed;
                lastIndex = key;
                break;
            case GLFW_RELEASE:
                keys[key] = InputKey::JustReleased;
                lastIndex = key;
                break;
            case GLFW_REPEAT:
                break;
        }
    }
}

// Correct input-related callbacks Static function
void Input::staticInputCallbackCorrection()
{
    instance->InputCallbackCorrection();
}

// Callback for mouse movement Static function
void Input::staticInputMouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    instance->InputMouseCallback(window, xpos, ypos);
}

// Callback for mouse scroll Static function
void Input::staticInputScrollCallback(GLFWwindow * window, double xoffset, double yoffset)
{
    instance->InputScrollCallback(window, xoffset, yoffset);
}

// Callback for keyboard input Static function
void Input::staticInputKeyCallback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
    instance->InputKeyCallback(window, key, scancode, action, mode);
}

Input * Input::Init(GLFWwindow * window)
{
    Input * input = new Input();
    if (input->Initialize(window))
        instance.reset(input);
    else
        delete input;
    return instance.get();
}

void Input::resetState()
{
    mouseMoved = mouseScrollMoved = false;
    positionOffset = scrollOffset = glm::vec2(0.0f, 0.0f);
}

void Input::updatePosition(double xpos, double ypos)
{
    mouseMoved = true;
    positionOffset.x = xpos - lastPosition.x;
    positionOffset.y = lastPosition.y - ypos;
    lastPosition.x = xpos;
    lastPosition.y = ypos;
}

// Get mouse position
glm::vec2 Input::getPosition() const
{
    return lastPosition;
}

// Get mouse position offset
glm::vec2 Input::getPositionOffset() const
{
    return positionOffset;
}

// Get mouse wheel offset
glm::vec2 Input::getWheelOffset() const
{
    // For now, using the same offset for X and Y
    return glm::vec2(positionOffset.x, positionOffset.y);
}

// Check if the mouse has moved
bool Input::mouseHasMoved() const
{
    return mouseMoved;
}

// Check if the mouse wheel has moved
bool Input::mouseScrollHasMoved() const
{
    return mouseMoved;
}

Input * Input::Get()
{
    return instance.get();
}