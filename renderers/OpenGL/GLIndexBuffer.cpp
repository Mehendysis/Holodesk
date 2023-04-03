//GLIndexBuffer.cpp
/*
A class that encapsulates a buffer containing index data (e.g. for defining triangles)
and provides functions to create and bind the buffer to the GPU.
*/
#include "GLIndexBuffer.h"

GLIndexBuffer::GLIndexBuffer(const GLuint* data, size_t size)
    : m_size(size)
{
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    m_usage = GL_STATIC_DRAW;
}

GLIndexBuffer::~GLIndexBuffer()
{
    glDeleteBuffers(1, &m_rendererID);
}

void GLIndexBuffer::Create(const void* data, GLsizei count)
{
}

void GLIndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
}

void GLIndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int GLIndexBuffer::GetCount() const
{
    return m_count;
}