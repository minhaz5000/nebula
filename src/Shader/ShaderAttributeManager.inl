#include "ShaderAttributeManager.h"

template <ShaderAttributeTypable T>
inline void ShaderAttributeManager::setShaderAttribute(const std::string &name, const T val)
{
    shaderAttributes[name] = std::make_unique<ShaderAttribute>(val);
}

template <ShaderAttributeTypableClass T>
inline void ShaderAttributeManager::setShaderAttribute(const std::string &name, const T &val)
{
    shaderAttributes[name] = std::make_unique<ShaderAttribute>(val);
}

template <ShaderAttributeTypableAny T>
inline T *ShaderAttributeManager::getShaderAttribute(const std::string &name)
{
    if (!shaderAttributes.contains(name))
    {
        return nullptr;
    }

    ShaderAttribute *attribute = shaderAttributes[name].get();
    return dynamic_cast<T *>(attribute->getData());
}

template <ShaderAttributeTypableAny T>
inline const T *ShaderAttributeManager::GetShaderAttribute(const std::string &name) const
{
    if (!shaderAttributes.contains(name))
    {
        return nullptr;
    }

    const ShaderAttribute *attribute = shaderAttributes.at(name).get();
    return dynamic_cast<const T *>(attribute->getData());
}
