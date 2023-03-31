#define WIN32_LEAN_AND_MEAN
//GLShaderProgram.h
#pragma once

#include <windows.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <memory>

using namespace std;

class GLShaderProgram {
public:
    GLShaderProgram();
    ~GLShaderProgram();

    void LoadShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
    void Compile();
    void Link();
    void Use() const;

    void SetUniform(const std::string& name, const glm::mat4& value) const;


    GLuint GetProgramId() const { return m_shaderProgramId; }

private:
    GLuint m_shaderProgramId;
    std::unique_ptr<GLShaderProgram> m_shaderProgram;

    GLuint m_vertexShaderId;
    GLuint m_fragmentShaderId;

    bool m_isCompiled;

    string ReadShaderFile(const string& fileName) const;
    GLuint CompileShader(const string& shaderSource, GLenum shaderType) const;
};
