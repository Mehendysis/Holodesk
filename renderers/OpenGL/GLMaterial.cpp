// GLMaterial.cpp

#include "GLMaterial.h"

GLMaterial::GLMaterial() :
    m_programID(0),
    m_projectionMatrixLoc(0),
    m_viewMatrixLoc(0),
    m_modelMatrixLoc(0)
{
    // Create the shader program and set up the locations of the uniform variables
    m_programID = glCreateProgram();
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Load and compile the vertex and fragment shaders

    // Attach the shaders to the program and link them together

    // Get the locations of the uniform variables
    m_projectionMatrixLoc = glGetUniformLocation(m_programID, "projectionMatrix");
    m_viewMatrixLoc = glGetUniformLocation(m_programID, "viewMatrix");
    m_modelMatrixLoc = glGetUniformLocation(m_programID, "modelMatrix");
}

void GLMaterial::UseProgram() const
{
    glUseProgram(m_programID);
}

void GLMaterial::SetProjectionMatrix(const glm::mat4& projectionMatrix)
{
    glUniformMatrix4fv(m_projectionMatrixLoc, 1, GL_FALSE, &projectionMatrix[0][0]);
}

void GLMaterial::SetViewMatrix(const glm::mat4& viewMatrix)
{
    glUniformMatrix4fv(m_viewMatrixLoc, 1, GL_FALSE, &viewMatrix[0][0]);
}

void GLMaterial::SetModelMatrix(const glm::mat4& modelMatrix)
{
    glUniformMatrix4fv(m_modelMatrixLoc, 1, GL_FALSE, &modelMatrix[0][0]);
}

void GLMaterial::SetUniforms(const glm::mat4& mvpMatrix) const
{
    // Set the uniform variables
    glUniformMatrix4fv(m_modelMatrixLoc, 1, GL_FALSE, &mvpMatrix[0][0]);
}
