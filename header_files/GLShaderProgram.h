//GLShaderProgram.h
//#define WIN32_LEAN_AND_MEAN
#pragma once

#include <glm/glm.hpp>
#include <string>
#include "GLMemoryWrapper.h"

class GLShaderProgram {
public:
    GLShaderProgram() : m_isCompiled(false), m_shaderProgramId(0), m_vertexShaderId(0), m_fragmentShaderId(0) {};

    ~GLShaderProgram();

    bool LoadShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
    void Use() const;
    void SetUniform(const std::string& name, const glm::mat4& value) const;
    bool LoadFile(const std::string& fileName, std::string& fileContent);
    const std::string& GetVertexShaderFile() const;
    const std::string& GetFragmentShaderFile() const;

    GLuint GetProgramId() const;
    GLuint Compile(const std::string& source, GLenum type);
    GLuint Link(GLuint vertexShader, GLuint fragmentShader);
    GLuint GetFragmentShaderId() const;

private:
    std::string m_vertexShaderFile = "vertex_shaders/GLSL_files/unlit_vertex.glsl";
    std::string m_fragmentShaderFile = "vertex_shaders/GLSL_files/unlit_fragment.glsl";

    GLuint m_shaderProgramId;
    std::unique_ptr<GLShaderProgram> m_shaderProgram;

    GLuint m_vertexShaderId;
    GLuint m_fragmentShaderId;

    bool m_isCompiled;

    std::string ReadShaderFile(const std::string& fileName) const;
};
