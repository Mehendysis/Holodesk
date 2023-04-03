//GLVertexBuffer.cpp
/*
A class that encapsulates a buffer containing vertex data (e.g. position, color, normal)
and provides functions to create and bind the buffer to the GPU.
*/

#include "GLVertexBuffer.h"

GLVertexBuffer::GLVertexBuffer(const void* data, size_t size, GLenum usage)
    : m_size(size), m_vertexCount(size / sizeof(GLfloat))
{
    // Create a new vertex buffer object
    glGenBuffers(1, &m_id);

    // Bind the vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, m_id);

    // Upload the vertex data to the GPU
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}


GLVertexBuffer::~GLVertexBuffer()
{
    // Delete the vertex buffer object
    glDeleteBuffers(1, &m_id);
}

void GLVertexBuffer::Bind() const
{
    // Bind the vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void GLVertexBuffer::Unbind() const
{
    // Unbind the vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLVertexBuffer::SetData(const void* data, size_t size, GLenum usage)
{
    // Bind the vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, m_id);

    // Upload the vertex data to the GPU
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);

    // Update the vertex buffer size and count
    m_size = size;
    m_vertexCount = size / sizeof(GLfloat);
}