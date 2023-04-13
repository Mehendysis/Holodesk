#ifndef VERTEXDATA_H
#define VERTEXDATA_H

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>

namespace VertexData {
    struct Vertex
    {
        float x, y, z; // position
        float r, g, b; // color
    };
}

// Define the index data for a cube
extern const GLuint g_cube_index_buffer_data[];

extern const GLfloat g_vertex_buffer_data[];

extern const int g_vertex_buffer_data_size;

extern const int g_index_buffer_size;

extern const GLuint g_index_buffer_data[];


#endif
