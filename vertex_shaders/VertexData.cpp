#include "VertexData.h"
#include <glad/glad.h>

struct Vertex
{
    float x, y, z; // position
    float r, g, b; // color
};

const GLfloat g_vertex_buffer_data[] = {
    // Front face
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    // Back face
    -0.5f, -0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
    // Top face
    -0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
    // Bottom face
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    // Right face
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    // Left face
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
};


const GLuint g_element_buffer_data[] = {
    // Front face
    0, 1, 2,
    2, 3, 0,
    // Back face
    4, 5, 6,
    6, 7, 4,
    // Top face
    8, 9, 10,
    10, 11, 8,
    // Bottom face
    12, 13, 14,
    14, 15, 12,
    // Right face
    16, 17, 18,
    18, 19, 16,
    // Left face
    20, 21, 22,
    22, 23, 20
};



const GLuint g_index_buffer_data[] = 
{
    0, 1, 2, // front
    2, 3, 0,

    1, 5, 6, // right
    6, 2, 1,

    7, 6, 5, // back
    5, 4, 7,

    4, 0, 3, // left
    3, 7, 4,

    4, 5, 1, // bottom
    1, 0, 4,

    3, 2, 6, // top
    6, 7, 3
};

const int g_num_elements = sizeof(g_element_buffer_data) / sizeof(GLuint);
const int g_index_buffer_size = sizeof(g_index_buffer_data) / sizeof(GLuint);
const int g_vertex_buffer_data_size = 108;