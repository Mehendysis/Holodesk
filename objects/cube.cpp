
//#include <vector>
//#include <glm/glm.hpp>
//#include <glm/mat4x4.hpp>

#include <glm/gtc/type_ptr.hpp>
//#include <GLFW/glfw3.h>
#include <iostream>
//#include <fstream>
//#include <string>

#include "GLMemoryWrapper.h"
#include "cube.h"
//#include "GLShaderLoader.h"

//#include "utils.h"
using namespace std;

Cube::Cube() : shaderLoader("vertex_shaders/cube.vert", "vertex_shaders/cube.frag")
{
    // Create vertex array object
    glad_glGenVertexArrays(1, &m_VAO);
    glad_glBindVertexArray(m_VAO);

    // Create vertex buffer object
    glad_glGenBuffers(1, &m_VBO);
    glad_glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_cubeVertices), m_cubeVertices, GL_STATIC_DRAW);

    // Create element buffer object
    glad_glGenBuffers(1, &m_EBO);
    glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_cubeIndices), m_cubeIndices, GL_STATIC_DRAW);

    // Get the shader program ID
    shaderProgram = shaderLoader.getProgram();

    if (shaderProgram == 0) {
        std::cerr << "Error: Shader program creation failed." << std::endl;
    }

    // Set vertex attribute pointers
    GLint posAttrib = glad_glGetAttribLocation(shaderProgram, "position");
    glad_glEnableVertexAttribArray(posAttrib);
    glad_glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Set model view matrix uniform location
    m_modelViewLocation = glad_glGetUniformLocation(shaderProgram, "modelViewMatrix");
}


Cube::~Cube()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}

void Cube::initialize(GLuint shaderProgram) 
{
    this->shaderProgram = shaderProgram;

    m_numIndices = sizeof(m_cubeIndices) / sizeof(m_cubeIndices[0]);

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_cubeVertices), m_cubeVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_cubeIndices), m_cubeIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}


void Cube::draw(const glm::mat4& modelViewMatrix, const glm::mat4& projectionMatrix)
{
    // Use shader program
    glUseProgram(shaderProgram);

    // Set the model view matrix in the shader
    GLint modelViewLoc = glGetUniformLocation(shaderProgram, "modelViewMatrix");
    if (modelViewLoc != -1) {
        glUniformMatrix4fv(modelViewLoc, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
    }
    else {
        cerr << "ERROR::CUBE::UNIFORM_LOCATION_NOT_FOUND: modelViewMatrix" << endl;
    }

    // Set the projection matrix in the shader
    GLint projectionLoc = glGetUniformLocation(shaderProgram, "projectionMatrix");

    if (projectionLoc != -1) {
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    }
    else {
        cerr << "ERROR::CUBE::UNIFORM_LOCATION_NOT_FOUND: projection" << endl;
    }

    // Bind VAO and draw
    glBindVertexArray(this->m_VAO);

    glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}



GLuint Cube::getShaderProgram() const 
{
    return shaderProgram;
}