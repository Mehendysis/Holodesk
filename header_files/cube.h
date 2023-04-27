
#ifndef CUBE_H
#define CUBE_H

#include <glm/glm.hpp>
#include "GLShaderloader.h"

class Cube {
public:
    Cube();
    ~Cube();
    GLuint getShaderProgram() const;
    void draw(const glm::mat4& modelViewMatrix, const glm::mat4& projectionMatrix);
    void initialize(GLuint shaderProgram);

private:
    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_EBO;
    GLuint shaderProgram;
    GLuint m_numIndices;
    GLuint m_modelViewLocation;
    GLShaderLoader shaderLoader;
    GLfloat m_cubeVertices[24] = {
        // Front face
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        // Back face
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f
    };
    GLuint m_cubeIndices[36] = {
        // Front face
        0, 1, 2,
        2, 3, 0,
        // Back face
        4, 5, 6,
        6, 7, 4,
        // Top face
        3, 2, 6,
        6, 7, 3,
        // Bottom face
        0, 1, 5,
        5, 4, 0,
        // Left face
        0, 3, 7,
        7, 4, 0,
        // Right face
        1, 2, 6,
        6, 5, 1
    };

};

#endif // CUBE_H
