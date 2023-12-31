#include "Renderer.h"
#include <iostream>

Renderer::Renderer() : currentShader{nullptr}
{
	GLfloat quadVertices[] = {
        -1.0f, -1.0f,
         1.0f, -1.0f,
        -1.0f,  1.0f,
         1.0f, -1.0f,
         1.0f,  1.0f,
        -1.0f,  1.0f
    };

    glGenVertexArrays(1, &vao);
    if (vao == 0) {
        // Handle error
        std::cerr << "Failed to generate VAO!" << std::endl;
    }
    glGenBuffers(1, &vbo);
    if (vbo == 0) {
        // Handle error
        std::cerr << "Failed to generate VBO!" << std::endl;
    }

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    // Specify the layout of the vertex data
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Renderer::~Renderer()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

GLuint Renderer::getVAO()
{
	return vao;
}
GLuint Renderer::getVBO()
{
	return vbo;
}

void Renderer::setCurrentShader(Constants::Shaders::ShaderID shaderID)
{
    currentShader = &getShader(shaderID);
}

void Renderer::useCurrentShader() const
{
    currentShader->use();
}

Shader * Renderer::getCurrentShader() const
{
	return currentShader;
}

void Renderer::loadShaders(const std::unordered_map<Constants::Shaders::ShaderID, std::pair<std::string, std::string>> &shaderFiles)
{
	for (const auto& shaderEntry : shaderFiles) {
        const auto& shaderID = shaderEntry.first;
        const auto& filePaths = shaderEntry.second;

        auto shader = std::make_unique<Shader>(filePaths.first.c_str(), filePaths.second.c_str());
        shaders.emplace(shaderID, std::move(shader));
    }
}

Shader & Renderer::getShader(const Constants::Shaders::ShaderID shaderID)
{
	return *shaders.at(shaderID);
}

void Renderer::draw()
{
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
