//VertexCube.h
#include <windows.h>
#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>

class VertexCube
{
public:
    unsigned int GetIndexCount() const { return static_cast<unsigned int>(m_indices.size()); }

    VertexCube(float sideLength = 1.0f, int id = 0);

    void Render() const;

    void Update(float deltaTime);

    glm::mat4 GetModelMatrix() const;

    void SetPosition(const glm::vec3& position);
    glm::vec3 GetPosition() const;

    void SetSize(float size);
    float GetSize() const;

    void SetId(unsigned int id);
    unsigned int GetId() const;

    bool IntersectRay(const glm::vec3& origin, const glm::vec3& direction, float& t) const;

    GLuint GetVertexBuffer() const { return m_vertexBuffer; }
    GLuint GetIndexBuffer() const { return m_indexBuffer; }

private:
    GLuint m_indexBuffer;
    GLuint m_vertexBuffer;
    float m_sideLength;
    float m_size;
    int m_id;
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
    glm::mat4 m_modelMatrix;
    glm::mat4 m_viewMatrix;
    glm::mat4 m_projectionMatrix;
    glm::mat4 m_mvpMatrix;

    std::vector<glm::vec3> m_vertices;
    std::vector<unsigned int> m_indices;
};