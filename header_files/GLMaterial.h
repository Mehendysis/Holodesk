// GLMaterial.h
#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>

class GLMaterial
{
public:
    GLMaterial();

    void UseProgram() const;

    void SetProjectionMatrix(const glm::mat4& projectionMatrix);
    void SetViewMatrix(const glm::mat4& viewMatrix);
    void SetModelMatrix(const glm::mat4& modelMatrix);

    void SetUniforms(const glm::mat4& mvpMatrix) const;

private:
    GLuint m_programID;
    GLuint m_projectionMatrixLoc;
    GLuint m_viewMatrixLoc;
    GLuint m_modelMatrixLoc;
    GLuint m_textureLoc;
};
