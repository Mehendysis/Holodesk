//PointCloudCube.h
#pragma once

#include <glm/glm.hpp>
#include <vector>

class PointCloudCube {
public:
    PointCloudCube(float sideLength, int id);

    void Render() const;
    void Update(float deltaTime);

    // Getters and setters for position, size and id
    void SetPosition(const glm::vec3& position);
    glm::vec3 GetPosition() const;
    void SetSize(float size);
    float GetSize() const;
    void SetId(unsigned int id);
    unsigned int GetId() const;

    bool IntersectRay(const glm::vec3& origin, const glm::vec3& direction, float& t) const;

private:
    std::vector<glm::vec3> m_points;
    std::vector<unsigned int> m_indices;

    float m_sideLength;
    int m_id;
};
