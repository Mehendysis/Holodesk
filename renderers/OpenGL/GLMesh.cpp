//GLMesh.cpp
/*
A class that encapsulates a set of vertices and indices, 
along with any other information needed to render the mesh 
(e.g. texture coordinates, material properties).
*/
#include "GLMesh.h"
#include <string>
#include <vector>
#include <glad/glad.h>

GLMesh::GLMesh()
{
    // Cube vertices
    std::vector<GLfloat> vertices = {
        // Front face
        -1.0f, -1.0f,  1.0f, // Bottom left
         1.0f, -1.0f,  1.0f, // Bottom right
         1.0f,  1.0f,  1.0f, // Top right
        -1.0f,  1.0f,  1.0f, // Top left

        // Back face
        -1.0f, -1.0f, -1.0f, // Bottom left
         1.0f, -1.0f, -1.0f, // Bottom right
         1.0f,  1.0f, -1.0f, // Top right
        -1.0f,  1.0f, -1.0f, // Top left
    };

    // Cube indices
    std::vector<GLuint> indices = {
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

        // Right face
        1, 2, 6,
        6, 5, 1,

        // Left face
        0, 3, 7,
        7, 4, 0
    };

    // Initialize the transformation matrix
    m_transform = glm::mat4(1.0f);

    // Vertex buffer
    m_vertexBuffer = std::make_unique<GLVertexBuffer>(&vertices[0], sizeof(GLfloat) * vertices.size(), GL_STATIC_DRAW);
   
    // Index buffer
    m_indexBuffer = std::make_unique<GLIndexBuffer>(&indices[0], indices.size());

    // Set the vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer->GetID());
}

GLMesh::~GLMesh()
{
    // Delete the vertex buffer object
    if (m_vertexBuffer)
    {
        m_vertexBuffer.reset();
    }

    // Delete the index buffer object
    if (m_indexBuffer)
    {
        m_indexBuffer.reset();
    }

    // Delete the material object
    if (m_material)
    {
        delete m_material;
        m_material = nullptr;
    }
}

void GLMesh::Render() const
{
    // Bind the vertex buffer
    m_vertexBuffer->Bind();

    // Bind the index buffer
    m_indexBuffer->Bind();

    // Draw the mesh
    glDrawElements(GL_TRIANGLES, m_indexBuffer->GetCount(), GL_UNSIGNED_INT, 0);

}

void GLMesh::SetPosition(const glm::vec3& position)
{
    // Set the position of the mesh
    // Update the transformation matrix with the new position
    m_transform[3] = glm::vec4(position, 1.0f);
}

void GLMesh::SetRotation(const glm::vec3& rotation)
{
    // Set the rotation of the mesh
    // Here is a simple example using a rotation quaternion
    glm::quat rotationQuat = glm::quat(glm::radians(rotation));

    // Apply the rotation to the mesh's transformation matrix
    m_transform = glm::mat4_cast(rotationQuat) * m_transform;
}
