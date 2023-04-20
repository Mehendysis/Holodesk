//GLIndexBuffer.h
#pragma once

#include "GLMemoryWrapper.h"
//#include <glad/glad.h>

class GLIndexBuffer {
public:
    GLIndexBuffer(const GLuint* data, size_t size);
    ~GLIndexBuffer();

    void Create(const void* data, GLsizei count);

    void Bind() const;
    void Unbind() const;

    unsigned int GetCount() const;

    GLuint GetID() const { return m_id; }
    
    size_t GetSize() const { return m_size; }
    size_t GetIndexCount() const { return m_indexCount; }

    inline GLuint GetIndexBufferID() const { return m_indexBufferID; }

private:
    GLuint m_id;
    size_t m_size;
    size_t m_vertexCount;
    size_t m_indexCount;
    GLuint m_indexBufferID;
    GLsizei m_count;
    GLenum m_usage;
    unsigned int m_rendererID;
};
