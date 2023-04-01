#include "PointCloudCube.h"

PointCloudCube::PointCloudCube(float sideLength, int id)
    : m_sideLength(sideLength), m_id(id)
{
    // Define the points of the cube
    // Each point only needs to store its position relative to the center point
    m_points.push_back(glm::vec3(-0.5f, -0.5f, -0.5f) * m_sideLength); // Point 0
    m_points.push_back(glm::vec3(-0.5f, -0.5f, 0.5f) * m_sideLength);  // Point 1
    m_points.push_back(glm::vec3(-0.5f, 0.5f, -0.5f) * m_sideLength);  // Point 2
    m_points.push_back(glm::vec3(-0.5f, 0.5f, 0.5f) * m_sideLength);   // Point 3
    m_points.push_back(glm::vec3(0.5f, -0.5f, -0.5f) * m_sideLength);  // Point 4
    m_points.push_back(glm::vec3(0.5f, -0.5f, 0.5f) * m_sideLength);   // Point 5
    m_points.push_back(glm::vec3(0.5f, 0.5f, -0.5f) * m_sideLength);   // Point 6
    m_points.push_back(glm::vec3(0.5f, 0.5f, 0.5f) * m_sideLength);    // Point 7

    // Define the indices of the cube
    // Each face of the cube is made up of two triangles
    m_indices = {
        0, 2, 3,
        0, 3, 1,
        0, 4, 6,
        0, 6, 2,
        0, 1, 5,
        0, 5, 4,
        7, 5, 1,
        7, 1, 3,
        7, 3, 2,
        7, 2, 6,
        7, 6, 4,
        7, 4, 5
    };
}

void PointCloudCube::Render() const
{
}

void PointCloudCube::Update(float deltaTime)
{
}

void PointCloudCube::SetPosition(const glm::vec3& position)
{
}

glm::vec3 PointCloudCube::GetPosition() const
{
    return glm::vec3();
}

void PointCloudCube::SetSize(float size)
{
}

float PointCloudCube::GetSize() const
{
    return 0.0f;
}

void PointCloudCube::SetId(unsigned int id)
{
}

unsigned int PointCloudCube::GetId() const
{
    return 0;
}

bool PointCloudCube::IntersectRay(const glm::vec3& origin, const glm::vec3& direction, float& t) const
{
    return false;
}
