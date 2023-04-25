
//VertexCube.cpp

#include "VertexCube.h"
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

VertexCube::VertexCube(float sideLength, int id)
    : m_sideLength(sideLength), m_id(id)
{
    // Define the vertices of the cube
    // Each vertex stores its position in 3D space
    // The first 8 vertices define the corners of the cube, and the last 8 vertices define the center points of each face
    m_vertices = 
    {
        // Corners
        glm::vec3(-0.5f, -0.5f, -0.5f) * m_sideLength, // Vertex 0
        glm::vec3(-0.5f, -0.5f, 0.5f) * m_sideLength,  // Vertex 1
        glm::vec3(-0.5f, 0.5f, -0.5f) * m_sideLength,  // Vertex 2
        glm::vec3(-0.5f, 0.5f, 0.5f) * m_sideLength,   // Vertex 3
        glm::vec3(0.5f, -0.5f, -0.5f) * m_sideLength,  // Vertex 4
        glm::vec3(0.5f, -0.5f, 0.5f) * m_sideLength,   // Vertex 5
        glm::vec3(0.5f, 0.5f, -0.5f) * m_sideLength,   // Vertex 6
        glm::vec3(0.5f, 0.5f, 0.5f) * m_sideLength,    // Vertex 7

        // Centers of faces
        glm::vec3(0.0f, 0.0f, -0.5f) * m_sideLength, // Vertex 8
        glm::vec3(0.0f, 0.0f, 0.5f) * m_sideLength,  // Vertex 9
        glm::vec3(0.0f, -0.5f, 0.0f) * m_sideLength, // Vertex 10
        glm::vec3(0.0f, 0.5f, 0.0f) * m_sideLength,  // Vertex 11
        glm::vec3(-0.5f, 0.0f, 0.0f) * m_sideLength, // Vertex 12
        glm::vec3(0.5f, 0.0f, 0.0f) * m_sideLength   // Vertex 13
    };
}



void VertexCube::Render() const
{
    // Bind the VBO and IBO
    // TODO: Implement

    // Set the vertex attribute pointers
    // TODO: Implement

    // Set any uniform variables for the shader program
    // TODO: Implement

    // Draw the cube using the indices in the IBO
    // TODO: Implement
}

void VertexCube::Update(float deltaTime)
{
    // Update the model matrix based on any changes to position, rotation, or scale
    m_modelMatrix = glm::translate(glm::mat4(1.0f), m_position);
    m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    m_modelMatrix = glm::rotate(m_modelMatrix, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(m_scale));

    // Update the MVP matrix
    m_mvpMatrix = m_projectionMatrix * m_viewMatrix * m_modelMatrix;
}

glm::mat4 VertexCube::GetModelMatrix() const
{
    return m_modelMatrix;
}


void VertexCube::SetPosition(const glm::vec3& position)
{
    m_position = position;
    // Update the model matrix to reflect the new position
    m_modelMatrix = glm::translate(glm::mat4(1.0f), m_position);
}

glm::vec3 VertexCube::GetPosition() const
{
    return glm::vec3();
}

void VertexCube::SetSize(float size)
{
    m_size = size;

    // Update the vertex positions to reflect the new size
    m_vertices[0] = glm::vec3(-0.5f, -0.5f, -0.5f) * m_size;
    m_vertices[1] = glm::vec3(-0.5f, -0.5f, 0.5f) * m_size;
    m_vertices[2] = glm::vec3(-0.5f, 0.5f, -0.5f) * m_size;
    m_vertices[3] = glm::vec3(-0.5f, 0.5f, 0.5f) * m_size;
    m_vertices[4] = glm::vec3(0.5f, -0.5f, -0.5f) * m_size;
    m_vertices[5] = glm::vec3(0.5f, -0.5f, 0.5f) * m_size;
    m_vertices[6] = glm::vec3(0.5f, 0.5f, -0.5f) * m_size;
    m_vertices[7] = glm::vec3(0.5f, 0.5f, 0.5f) * m_size;
}


float VertexCube::GetSize() const
{
    return 0.0f;
}

void VertexCube::SetId(unsigned int id)
{
    m_id = id;
}

unsigned int VertexCube::GetId() const
{
    return m_id;
}

bool VertexCube::IntersectRay(const glm::vec3& origin, const glm::vec3& direction, float& t) const
{
    // Check if ray intersects the bounding box of the cube
    float tmin = -std::numeric_limits<float>::max();
    float tmax = std::numeric_limits<float>::max();

    glm::vec3 p = m_position - origin;

    if (glm::abs(direction.x) < std::numeric_limits<float>::epsilon()) {
        if (p.x > 0.5f || p.x < -0.5f) {
            return false;
        }
    }
    else {
        float invDir = 1.0f / direction.x;
        float t1 = (0.5f - p.x) * invDir;
        float t2 = (-0.5f - p.x) * invDir;

        if (t1 > t2) {
            std::swap(t1, t2);
        }

        tmin = std::max(tmin, t1);
        tmax = std::min(tmax, t2);

        if (tmin > tmax) {
            return false;
        }
    }

    if (glm::abs(direction.y) < std::numeric_limits<float>::epsilon()) {
        if (p.y > 0.5f || p.y < -0.5f) {
            return false;
        }
    }
    else {
        float invDir = 1.0f / direction.y;
        float t1 = (0.5f - p.y) * invDir;
        float t2 = (-0.5f - p.y) * invDir;

        if (t1 > t2) {
            std::swap(t1, t2);
        }

        tmin = std::max(tmin, t1);
        tmax = std::min(tmax, t2);

        if (tmin > tmax) {
            return false;
        }
    }

    if (glm::abs(direction.z) < std::numeric_limits<float>::epsilon()) {
        if (p.z > 0.5f || p.z < -0.5f) {
            return false;
        }
    }
    else {
        float invDir = 1.0f / direction.z;
        float t1 = (0.5f - p.z) * invDir;
        float t2 = (-0.5f - p.z) * invDir;

        if (t1 > t2) {
            std::swap(t1, t2);
        }

        tmin = std::max(tmin, t1);
        tmax = std::min(tmax, t2);

        if (tmin > tmax) {
            return false;
        }
    }

    t = tmin;

    return true;
}
