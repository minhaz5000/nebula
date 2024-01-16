#include "Shader.h"
#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <sstream>
#include <iostream>

Shader::Shader(const GLchar * vertexPath, const GLchar * fragmentPath)
{
    // 1. Retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // Ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try {
        // Open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // Read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();       
        // Close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // Convert stream into string
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();     
    }
    catch(std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    const GLchar * vShaderCode = vertexCode.c_str();
    const GLchar * fShaderCode = fragmentCode.c_str();

    // 2. Compile shaders
    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];

    // Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);

    // Print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    // Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    // Print compile errors if any
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    // Shader Program
    programID = glCreateProgram();
    glAttachShader(programID, vertex);
    glAttachShader(programID, fragment);
    glLinkProgram(programID);

    // print linking errors if any
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(programID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // Delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() 
{ 
    glUseProgram(programID);
}

GLuint Shader::getUniformID(const GLchar * uniformName) const
{
    // Check if the uniform location is already in the cache
    auto it = uniformCache.find(uniformName);
    if (it != uniformCache.end()) {
        // Return the cached uniform location
        return it->second;
    }

    // If not found, retrieve the uniform location and cache it
    GLuint uniformId = glGetUniformLocation(programID, uniformName);
    if (uniformId == GL_INVALID_INDEX) {
        // Handle error: Uniform variable not found
        std::cerr << "Error: Uniform variable '" << uniformName
         << "' not found in the shader program." << std::endl;
    }

    // Cache the uniform location (even if it's GL_INVALID_INDEX)
    uniformCache[uniformName] = uniformId;

    return uniformId;
}

void Shader::setUniformBool(const GLchar * uniformName, const bool nb)
{         
    glUniform1i(getUniformID(uniformName), nb); 
}

void Shader::setUniformInt(const GLchar * uniformName, const GLint nb)
{
    glUniform1i(getUniformID(uniformName), nb);
}

void Shader::setUniformInt(const GLchar * uniformName, const std::vector<GLint> & nb)
{
    glUniform1iv(getUniformID(uniformName), nb.size(), nb.data());
}

void Shader::setUniformFloat(const GLchar * uniformName, const GLfloat nb)
{
    glUniform1f(getUniformID(uniformName), nb);
}

void Shader::setUniformVec2(const GLchar * uniformName, const glm::vec2 & nbs)
{
    glUniform2fv(getUniformID(uniformName), 1, glm::value_ptr(nbs));
}

void Shader::setUniformFloat(const GLchar * uniformName, const GLfloat nb1, const GLfloat nb2)
{
    glUniform2f(getUniformID(uniformName), nb1, nb2);
}

void Shader::setUniformVec3(const GLchar * uniformName, const glm::vec3 & nbs)
{
    glUniform3fv(getUniformID(uniformName), 1, glm::value_ptr(nbs));
}

void Shader::setUniformFloat(const GLchar * uniformName, const GLfloat nb1, const GLfloat nb2, const GLfloat nb3)
{
    glUniform3f(getUniformID(uniformName), nb1, nb2, nb2);
}

void Shader::setUniformVec4(const GLchar * uniformName, const glm::vec4 & nbs)
{
    glUniform4fv(getUniformID(uniformName), 1, glm::value_ptr(nbs));
}

void Shader::setUniformFloat(const GLchar* uniformName, const GLfloat nb1, const GLfloat nb2, const GLfloat nb3, const GLfloat nb4)
{
    glUniform4f(getUniformID(uniformName), nb1, nb2, nb3, nb4);
}


void Shader::setUniformMatrix4f(const GLchar * uniformName, const glm::mat4 & mat)
{
    glUniformMatrix4fv(getUniformID(uniformName), 1, GL_FALSE, glm::value_ptr(mat));
}

Shader::~Shader()
{
    glDeleteProgram(programID);
}

void Shader::ClearUniformCache()
{
    uniformCache.clear();
}
