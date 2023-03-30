#include "ProjectionMatrix.h"
#include <cmath>

ProjectionMatrix::ProjectionMatrix(float fov, float aspect_ratio, float near_plane, float far_plane) 
{
    // TODO: implement constructor
}

void ProjectionMatrix::set_fov(float fov) 
{
    // TODO: implement set_fov
}

void ProjectionMatrix::set_aspect_ratio(float aspect_ratio) 
{
    // TODO: implement set_aspect_ratio
}

void ProjectionMatrix::set_near_plane(float near_plane) 
{
    // TODO: implement set_near_plane
}

void ProjectionMatrix::set_far_plane(float far_plane) 
{
    // TODO: implement set_far_plane
}

const float* ProjectionMatrix::data() const
{
    return &projectionMatrix[0];
}


void ProjectionMatrix::calculate_projection_matrix(float distance)
{
    // Calculate the aspect ratio
    float aspect_ratio = static_cast<float>(m_viewport_width) / m_viewport_height;

    // Calculate the field of view in radians
    float fov_radians = glm::radians(m_fov);

    // Calculate the FOV angle based on the distance
    float fov = 45.0f; // Default FOV angle
    if (distance > 100.0f) {
        fov = 30.0f; // Lower FOV angle for far objects
    }

    // Calculate the distance to the near and far clipping planes
    float near_distance = m_near_plane;
    float far_distance = m_far_plane;

    // Calculate the projection matrix
    m_projection_matrix = glm::perspective(fov_radians, aspect_ratio, near_distance, far_distance);
}
