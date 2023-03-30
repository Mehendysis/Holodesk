#define WIN32_LEAN_AND_MEAN
//GLShaderProgram.h
#pragma once
#include <windows.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

class GLShaderProgram {
public:
    GLShaderProgram();
    ~GLShaderProgram();

    void LoadShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
    void Compile();
    void Link();
    void Use() const;

    void SetUniform(const std::string& name, bool value) const;
    void SetUniform(const std::string& name, int value) const;
    void SetUniform(const std::string& name, float value) const;
    void SetUniform(const std::string& name, const glm::vec3& value) const;
    void SetUniform(const std::string& name, const glm::mat4& value) const;

private:
    GLuint m_shaderProgramId;
    GLuint m_vertexShaderId;
    GLuint m_fragmentShaderId;

    bool m_isCompiled;

    std::string ReadShaderFile(const std::string& fileName) const;
    GLuint CompileShader(const std::string& shaderSource, GLenum shaderType) const;
};
