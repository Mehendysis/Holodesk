//GLShaderProgram.h
//#define WIN32_LEAN_AND_MEAN
#pragma once

#include <glm/glm.hpp>
#include <string>
#include "GLMemoryWrapper.h"

class GLRenderer;

class GLShaderProgram {
public:
    GLShaderProgram(GLRenderer* glRenderer);
    GLShaderProgram();

    ~GLShaderProgram();

    bool LoadShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
    void Use(GLuint shaderProgramId) const;
    void SetUniform(const std::string& name, const glm::mat4& value) const;
    bool LoadFile(const std::string& fileName, std::string& fileContent);
    const std::string& GetVertexShaderFile() const;
    const std::string& GetFragmentShaderFile() const;

    bool CheckShaderCompilation(GLuint shaderId);
    GLuint Compile(const std::string& source, GLenum type);
    GLuint Link(GLuint vertexShader, GLuint fragmentShader);
    //GLuint GetProgramId() const;
    //GLuint& GetProgramId();
    //GLuint& GetProgramId() const;
    const GLuint& GetProgramId() const;
    GLuint GetFragmentShaderId() const;
    GLuint GetVertexShaderId() const;
    void CallPrivateClean();
    bool IsCompiled() const;

private:
    GLRenderer* m_glRenderer;
    void PrivateClean();
    GLuint m_vertexShaderId;
    GLuint m_fragmentShaderId;
    std::string m_vertexShaderFile = "vertex_shaders/GLSL_files/unlit_vertex.glsl";
    std::string m_fragmentShaderFile = "vertex_shaders/GLSL_files/unlit_fragment.glsl";

    GLuint m_shaderProgramId;
    std::unique_ptr<GLShaderProgram> m_shaderProgram;

    bool m_isCompiled;

    std::string ReadShaderFile(const std::string& fileName) const;
};
