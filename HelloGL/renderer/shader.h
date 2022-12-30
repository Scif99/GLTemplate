#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>
#include <glm/glm.hpp>

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "gl_wrappers.h"

/*
- Note that our shader class is an OpenGL wrapper.
- Therefore we should ensure the class is non-copyable
*/


//--------------------
//SHADER
//---------------------

class GLShader
{
private:
    void CheckCompileErrors(unsigned int shader, std::string type);
   
public:
    GLID m_renderer_ID;
public:
    GLShader() = default;
    ~GLShader() { glDeleteProgram(m_renderer_ID.Value()); }
    GLShader(const GLShader& other) = default;
    GLShader& operator=(const GLShader& other) = default;
    GLShader(GLShader&& other) = default;
    GLShader& operator=(GLShader&& other) = default;

    GLShader(const char* vertexPath, const char* fragmentPath);

    //compile shader 
    void Compile(const char* vShaderCode, const char* fShaderCode);
    // use/activate the shader
    void Use();
    // utility functions that set values of uniforms
    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetVec2(const std::string& name, const glm::vec2& vec) const;
    void SetVec3(const std::string& name, const glm::vec3& vec) const;
    void SetMat4(const std::string& name, const glm::mat4& mat) const;

};
#endif 

