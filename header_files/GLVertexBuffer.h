// GLVertexBuffer.h
#pragma once

#include <glad/glad.h>
//#include <cstddef>

class GLVertexBuffer
{
public:
    GLVertexBuffer(const void* data, size_t size, GLenum usage);

    ~GLVertexBuffer();

    void Bind() const;
    void Unbind() const;

    void SetData(const void* data, size_t size, GLenum usage);

    GLuint GetID() const { return m_id; }
    size_t GetSize() const { return m_size; }
    size_t GetVertexCount() const { return m_vertexCount; }

private:
    GLuint m_id;
    size_t m_size;
    size_t m_vertexCount;
};