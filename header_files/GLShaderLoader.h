#ifndef SHADERLOADER_H
#define SHADERLOADER_H

#include <string>
#include "GLMemoryWrapper.h"

class GLShaderLoader {
public:
    GLShaderLoader(const char* vertexShaderPath, const char* fragmentShaderPath);
    ~GLShaderLoader();
    void use() const;
    GLuint getProgram() const;

private:
    GLuint programID;
    std::string m_vertexPath;
    std::string m_fragmentPath;
    std::string m_vertexShaderSource;
    std::string m_fragmentShaderSource;
    GLuint m_shaderProgram;
    GLuint loadShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    std::string loadShaderSource(const char* shaderPath) const;
    void checkShaderErrors(GLuint shaderID);
    void checkProgramErrors(GLuint programID);
};

#endif // SHADERLOADER_H
