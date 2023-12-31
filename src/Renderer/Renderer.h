#pragma once
#include "../Shader/Shader.h"
#include "../Shader/ShaderAttribute.h"
#include <memory>
#include "../Constants.h"

class Renderer
{

private:
    GLuint vao, vbo;
    Shader * currentShader;                     // shader currently in use

public:
    Renderer();
    ~Renderer();

    GLuint getVAO();
    GLuint getVBO();

    void draw();
    void setCurrentShader(Constants::Shaders::ShaderID shaderID);
    void useCurrentShader() const;
    Shader * getCurrentShader() const;
    void loadShaders(const std::unordered_map<Constants::Shaders::ShaderID, std::pair<std::string, std::string>> & shaderFiles);
    Shader & getShader(Constants::Shaders::ShaderID shaderID);
    std::unordered_map<Constants::Shaders::ShaderID, std::unique_ptr<Shader>> shaders;
};
