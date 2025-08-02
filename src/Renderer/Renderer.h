#pragma once
#include "../Shader/Shader.h"
#include <memory>

class Renderer
{

private:
    GLuint vao, vbo;
    Shader * currentShader;          // shader currently in use
    std::string currentShaderName;   // name of current shader
    int shaderCount;

public:
    Renderer();
    ~Renderer();

    GLuint getVAO();
    GLuint getVBO();

    void draw();
    void setCurrentShader(std::string shaderName);
    void useCurrentShader() const;
    Shader * getCurrentShader() const;
    void loadShaders(const std::unordered_map<std::string, std::pair<std::string, std::string>> & shaderFiles);
    std::string getCurrentShaderName() const;
    int getShaderCount() const;

private:
    Shader & getShader(std::string shaderName);
    std::unordered_map<std::string, std::unique_ptr<Shader>> shaders;
};
