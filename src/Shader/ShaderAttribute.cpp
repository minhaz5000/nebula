#include "ShaderAttribute.h"
#include <iostream>

ShaderAttribute::ShaderAttribute(const int val)
    : data{std::make_unique<int>(val)}, dataType{ShaderAttributeType::Int} {}

ShaderAttribute::ShaderAttribute(const float val)
    : data{std::make_unique<float>(val)}, dataType{ShaderAttributeType::Float} {}

ShaderAttribute::ShaderAttribute(const glm::mat4 &val)
    : data{std::make_unique<glm::mat4>(val)}, dataType{ShaderAttributeType::Matrix} {}

void ShaderAttribute::applyAttribute(const std::string &name, Shader &shader) const
{
    switch (dataType)
    {
        case ShaderAttributeType::Int:
            shader.setUniformInt(name.c_str(), *static_cast<int *>(data.get()));
            break;
        case ShaderAttributeType::Float:
            shader.setUniformFloat(name.c_str(), *static_cast<float *>(data.get()));
            break;
        case ShaderAttributeType::Matrix:
            shader.setUniformMatrix4f(name.c_str(), *static_cast<glm::mat4 *>(data.get()));
            break;
        default:
            throw std::runtime_error("Unknown ShaderAttributeType for attribute: " + name);
    }
}


const void * ShaderAttribute::getData() const
{
    return data.get();
}
