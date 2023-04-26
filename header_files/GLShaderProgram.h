//GLShaderProgram.h
//#define WIN32_LEAN_AND_MEAN
#pragma once

#include <glm/glm.hpp>
#include <string>
#include "GLMemoryWrapper.h"

class GLRenderer;

class GLShaderProgram {
public:
    //GLShaderProgram(std::unique_ptr<GLRenderer> glRenderer);

    GLShaderProgram();

    ~GLShaderProgram();

    bool LoadFile(const std::string& fileName, std::string& fileContent);
    bool CheckShaderCompilation(GLuint shaderId);
    bool IsCompiled() const;
    int generateShaders();
    bool LoadShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);

    void Use(GLuint shaderProgramId) const;
    void SetUniform(const std::string& name, const glm::mat4& value) const;
    void CallPrivateClean();

    const std::string& GetVertexShaderFile() const;
    const std::string& GetFragmentShaderFile() const;
    const GLuint& GetProgramId() const;

    GLuint Compile(const std::string& source, GLenum type);
    GLuint Link(GLuint vertexShader, GLuint fragmentShader);
    GLuint GetFragmentShaderId() const;
    GLuint GetVertexShaderId() const;


private:
    bool m_isCompiled;

    void PrivateClean();

    GLuint m_vertexShaderId;
    GLuint m_fragmentShaderId;
    GLuint m_shaderProgramId;

    std::unique_ptr<GLRenderer> m_glRenderer;

    //std::string m_vertexShaderFile = "vertex_shaders/GLSL_files/unlit_vertex.glsl";
    //std::string m_fragmentShaderFile = "vertex_shaders/GLSL_files/unlit_fragment.glsl";

    std::string m_vertexShaderFile = "vertex_shaders/cube.vert";
    std::string m_fragmentShaderFile = "vertex_shaders/cube.frag";

    std::string ReadShaderFile(const std::string& fileName) const;
    std::unique_ptr<GLShaderProgram> m_shaderProgram;
};
