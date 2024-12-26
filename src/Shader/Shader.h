#pragma once

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <glm/glm.hpp>
#include <string>
#include <unordered_map>
#include <vector>

class Shader {
private:
    // Shader Program ID
    GLuint programID;

    // Cache uniform ids for faster lookup
    mutable std::unordered_map<std::string, GLuint> uniformCache;

    // Retrieve uniform ids
    GLuint getUniformID(const GLchar * uniformName) const;

public:
    // constructor reads the shader
    Shader(const GLchar * vertexPath, const GLchar * fragmentPath);

    // use/activate the shader
    void use();
    // utility uniform functions

    // Set Uniform bool variable
    void setUniformBool(const GLchar * uniformName, const bool nb);

    // Set Uniform int (single)
    void setUniformInt(const GLchar * uniformName, const GLint nb);

    // Set Uniform int (vector of integers)
    void setUniformInt(const GLchar * uniformName, const std::vector<GLint> & nb);

    // Set Uniform float (single)
    void setUniformFloat(const GLchar * uniformName, const GLfloat nb);

    // Set Uniform 2D vector (vec2)
    void setUniformVec2(const GLchar * uniformName, const glm::vec2 & nbs);

    // Set Uniform 2D vector using 2 float values
    void setUniformFloat(const GLchar * uniformName, const GLfloat nb1, const GLfloat nb2);

    // Set Uniform 3D vector (vec3)
    void setUniformVec3(const GLchar * uniformName, const glm::vec3 & nbs);

    // Set Uniform 3D vector using 3 float values
    void setUniformFloat(const GLchar * uniformName, const GLfloat nb1, const GLfloat nb2, const GLfloat nb3);

    // Set Uniform 4D vector using vec4
    void setUniformVec4(const GLchar * uniformName, const glm::vec4 & nbs);

    // Set Uniform 4D vector using 4 float values
    void setUniformFloat(const GLchar * uniformName, const GLfloat nb1, const GLfloat nb2, const GLfloat nb3, const GLfloat nb4);
    
    // Set Uniform 4x4 matrix using mat4
    void setUniformMatrix4f(const GLchar * uniformName, const glm::mat4 & mat);

    void ClearUniformCache();

    ~Shader();
};
  
