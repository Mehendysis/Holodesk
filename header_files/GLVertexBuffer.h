//GLVertexBuffer.h
#pragma once
#include <windows.h>
#include <glad/glad.h>

class GLVertexBuffer
{
public:
    GLVertexBuffer(const void* data, unsigned int size, GLenum usage);
    ~GLVertexBuffer();

    void Bind() const;
    void Unbind() const;

    void SetData(const void* data, unsigned int size, GLenum usage);

    GLuint GetID() const { return m_id; }
    unsigned int GetSize() const { return m_size; }

private:
    GLuint m_id;
    unsigned int m_size;
};
