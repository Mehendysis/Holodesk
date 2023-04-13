//GLShaderProgram.h
//#define WIN32_LEAN_AND_MEAN
#pragma once

//#include <windows.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <memory>

using namespace std;

class GLShaderProgram {
public:
    GLShaderProgram() : m_isCompiled(false), m_shaderProgramId(0), m_vertexShaderId(0), m_fragmentShaderId(0) {};

    ~GLShaderProgram();

    bool LoadShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
    void Use() const;
    void SetUniform(const std::string& name, const glm::mat4& value) const;
    bool LoadFile(const std::string& fileName, std::string& fileContent);

    GLuint GetProgramId() const { return m_shaderProgramId; }
    GLuint Compile(const std::string& source, GLenum type);
    GLuint Link(GLuint vertexShader, GLuint fragmentShader);
    GLuint GetFragmentShaderId() const;

private:
    GLuint m_shaderProgramId;
    std::unique_ptr<GLShaderProgram> m_shaderProgram;

    GLuint m_vertexShaderId;
    GLuint m_fragmentShaderId;

    bool m_isCompiled;

    
   
    string ReadShaderFile(const string& fileName) const;
};
