//GLVertexArray.cpp
/*
A class that encapsulates a vertex array object,
which is used to define the format of the vertex data
(e.g. the order and types of the attributes) and
link it to the shader program.
*/
#include "GLVertexArray.h"

GLVertexArray::GLVertexArray() 
{
    // Vertex data
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };
    // Generate VAO
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    // Generate VBO
    glGenBuffers(1, &m_VBO);

    // Bind VBO and set vertex data
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Unbind VAO
    glBindVertexArray(0);
}

void GLVertexArray::CreateTriangleVAO(GLuint& vertex_array_object)
{
    // Vertex data
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    // Generate VAO
    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);

    // Generate VBO
    GLuint vbo;
    glGenBuffers(1, &vbo);

    // Bind VBO and set vertex data
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Unbind VAO
    glBindVertexArray(0);
}

void GLVertexArray::Bind() 
{
    glBindVertexArray(m_VAO);
}

void GLVertexArray::Unbind() 
{
    glBindVertexArray(0);
}