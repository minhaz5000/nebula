#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "Shader.h"

// Need to extend for more types
// Not yet completed
enum class ShaderAttributeType
{
    Int,    // Uniform Variable Type int
    Float,  // Uniform Variable Type float
    Matrix  // Uniform Variable Type Matrix 4x4
};

class ShaderAttribute
{
private:
    std::unique_ptr<void> data; // hold data value
    ShaderAttributeType dataType;   //hold data type

public:
    // Need to add more type overloaded constructors
    ShaderAttribute(const int val);
    ShaderAttribute(const float val);
    ShaderAttribute(const glm::mat4 &val);

    void applyAttribute(const std::string &name, Shader &shader) const;
    const void * getData() const;
};
