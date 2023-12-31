#pragma once

#include "ShaderAttribute.h"

template <class T>
concept ShaderAttributeCompatible = requires(const T& val) {
    ShaderAttribute{val};
};

template<class T>
// Concept checking if the type is a class appropriate for shader attributes
concept ShaderAttributeTypable =
    std::is_same_v<T, float> 
 || std::is_same_v<T, int>
 || std::is_same_v<T, bool>
 || std::is_same_v<T, glm::mat4>;

template<class T>
// Concept checking if the type is a class appropriate for shader attributes
concept ShaderAttributeTypableClass =
    std::is_same_v<T, glm::mat4>;

template<class T>
// Concept checking if the type is appropriate for shader attributes (both primitives & classes)
concept ShaderAttributeTypableAny = ShaderAttributeTypable<T> || ShaderAttributeTypableClass<T>;

// Manages shader attributes for Entities
class ShaderAttributeManager
{
public:
    ShaderAttributeManager();
    ~ShaderAttributeManager();

    template <ShaderAttributeCompatible T>
    void setShaderAttribute(const std::string& name, const T& val);

    template <ShaderAttributeCompatible T>
    T* getShaderAttribute(const std::string& name);

    template <ShaderAttributeCompatible T>
    const T* getShaderAttribute(const std::string& name) const;

    std::unordered_map<std::string, std::unique_ptr<ShaderAttribute>> shaderAttributes;
};

#include "ShaderAttributeManager.inl"
